package com.example.alarmretry;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesClient;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.location.LocationClient;
import com.google.android.gms.maps.CameraUpdate;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.IntentSender;
import android.location.Criteria;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.Toast;

public class AlarmMapActivity extends Activity
	implements GooglePlayServicesClient.ConnectionCallbacks,
	GooglePlayServicesClient.OnConnectionFailedListener,
	LocationListener{

	private LocationClient mLocationClient;
	private WakeLock mWakeLock;
	private MediaPlayer mPlayer;
	private AudioManager mAm;
	GoogleMap map;
	
	private final String TAG = this.getClass().getSimpleName();
	private String PROXIMITY_ALERT = "com.example.embedded_text.PROXIMITY_ALERT";
	private final static int CONNECTION_FAILURE_RESOLUTION_REQUEST = 9000;
	private final static int WAKELOCK_DELAY = 1000 * 60 * 30; // 30 min
	
	boolean isOutside;
	
	ProximityAlertReceiver alertReceiver;
	
	@Override
	public void onBackPressed(){
		/* do nothing when back button pressed */
	}
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
		
		
        super.onCreate(savedInstanceState);
        setContentView(R.layout.alarmmap_activity);
        
        // set the volume with given value
        //short volume = getIntent().getShortExtra("volume", (short)10);	// not working....
        /*mAm = (AudioManager)getSystemService(AUDIO_SERVICE);
        mAm.setStreamVolume(AudioManager.STREAM_ALARM, 
        		(int)volume,
        		AudioManager.FLAG_SHOW_UI);*/
        
        mLocationClient = new LocationClient(this, this, this);
        
        // Map setting
        map = ((MapFragment)getFragmentManager().findFragmentById(R.id.map)).getMap();
        map.setMapType(GoogleMap.MAP_TYPE_NORMAL);
        map.setMyLocationEnabled(true);
        
        String strToneUri = getIntent().getStringExtra(AlarmManagerHelper.TONE);
        startMedia(strToneUri);
        
        // Wake-lock
        Runnable releaseWakelock = new Runnable() {

			@Override
			public void run() {
				getWindow().clearFlags(WindowManager.LayoutParams.FLAG_TURN_SCREEN_ON);
				getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				getWindow().clearFlags(WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED);
				getWindow().clearFlags(WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD);

				if (mWakeLock != null && mWakeLock.isHeld()) {
					mWakeLock.release();
				}
			}
		};

		new Handler().postDelayed(releaseWakelock, WAKELOCK_DELAY);
        
    }
    
	private void startMedia(String strUri){
		 mPlayer = new MediaPlayer();
	        try{
	        	if(strUri != null &&
	        		!strUri.equals("")){
	        		  Uri toneUri = Uri.parse(strUri);
	        		  if(toneUri != null){
	        			  mPlayer.setDataSource(this, toneUri);
	        			  mPlayer.setAudioStreamType(AudioManager.STREAM_ALARM);
	        			  mPlayer.setLooping(true);
	        			  mPlayer.prepare();
	        			  mPlayer.start();
	        		  }
	        	}
	        } catch(Exception e){
	        	e.printStackTrace();
	        }
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.map_activity_menu, menu);
		return true;
	}
	
	public boolean onOptionsItemSelected(MenuItem item) {
	       // Handle action bar item clicks here. The action bar will
	       // automatically handle clicks on the Home/Up button, so long
	       // as you specify a parent activity in AndroidManifest.xml.
	       int id = item.getItemId();
	       if (id == R.id.mapview_exit) {
	    	   if(true/*isOutside*/){
	    		   if(mPlayer != null)
	    			   mPlayer.release();
	    		    finish();
	    	   } else {
	    		   Toast.makeText(this, 
	    				   "Not enough,  Haha!! Gogo!!",
	    				   Toast.LENGTH_SHORT)
	    				   .show();
	    	   }
	    	 	    	   
	       }
	       return super.onOptionsItemSelected(item);
	   }

		
	@Override
	protected void onResume(){
		super.onResume();
		
		// Set the window to keep screen on
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_TURN_SCREEN_ON);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD);

		// Acquire wakelock
		PowerManager pm = (PowerManager) getApplicationContext().getSystemService(Context.POWER_SERVICE);
		if (mWakeLock == null) {
			mWakeLock = pm.newWakeLock((PowerManager.FULL_WAKE_LOCK | PowerManager.SCREEN_BRIGHT_WAKE_LOCK | PowerManager.ACQUIRE_CAUSES_WAKEUP), TAG);
		}
			if (!mWakeLock.isHeld()) {
			mWakeLock.acquire();
			Log.i(TAG, "Wakelock aquired!!");
		}
				
		alertReceiver = new ProximityAlertReceiver();
		IntentFilter filter = new IntentFilter(PROXIMITY_ALERT);
		registerReceiver(alertReceiver, filter);
	}
	
	@Override
	protected void onPause(){
		super.onPause();
		
		if(mWakeLock != null && mWakeLock.isHeld())
			mWakeLock.release();
		
		unregisterReceiver(alertReceiver);
	}
	
	@Override
	protected void onStop(){
		mLocationClient.disconnect();
		if(mPlayer != null)
			mPlayer.release();
		super.onStop();
	}
	
	@Override
	protected void onStart(){
		super.onStart();
    	if(isGooglePlayServicesAvailable()){
    		mLocationClient.connect();
    	}
	}
	
	private void addProximityAlert(LatLng ll, int radius){
    	LocationManager locMng = 
    			(LocationManager) getSystemService(LOCATION_SERVICE);
    	String bestProvider = getBestProvider(locMng);
    	if(bestProvider == null)
    		bestProvider = LocationManager.GPS_PROVIDER;
    	locMng.requestLocationUpdates(bestProvider, 500, 0.5f, this);
    	
    	Intent intent = new Intent(PROXIMITY_ALERT);
    	PendingIntent pendingIntent =
    			PendingIntent.getBroadcast(this, -1, intent, PendingIntent.FLAG_UPDATE_CURRENT);
    	
    	locMng.addProximityAlert(ll.latitude, ll.longitude, radius, -1, pendingIntent);
    }
	
    private String getBestProvider(LocationManager locationManager){
    	Criteria criteria = new Criteria();
    	criteria.setAccuracy(Criteria.ACCURACY_FINE);
    	criteria.setPowerRequirement(Criteria.POWER_MEDIUM);
    	criteria.setAltitudeRequired(false);
    	criteria.setBearingRequired(false);
    	criteria.setSpeedRequired(false);
    	criteria.setCostAllowed(false);
    	
    	String provider = locationManager.getBestProvider(criteria, true);
    	return provider;
    }
	
	
    @Override
    protected void onActivityResult(
    		int requestCode, int resultCode, Intent data){
    	switch(requestCode){
    	case CONNECTION_FAILURE_RESOLUTION_REQUEST:
    		switch(resultCode){
    		case Activity.RESULT_OK:
    			mLocationClient.connect();
    			break;
    		}
    	}
    }
    
    private boolean isGooglePlayServicesAvailable(){
    	int resultCode = GooglePlayServicesUtil.isGooglePlayServicesAvailable(this);
    	if(ConnectionResult.SUCCESS == resultCode){
    		Log.d("Location Update", "Google Play Services is available");
    		return true;
    	} else {
    		Toast.makeText(this, "Not available", Toast.LENGTH_SHORT).show();
    		return false;
    	}
    }
    
    @Override
	public void onConnectionFailed(ConnectionResult arg0) {
		// TODO Auto-generated method stub
		if(arg0.hasResolution()){
			try{
				arg0.startResolutionForResult(this, CONNECTION_FAILURE_RESOLUTION_REQUEST);
			} catch(IntentSender.SendIntentException e){
				e.printStackTrace();
			}
		} else{
			Toast.makeText(getApplicationContext(), "Location Services not available", Toast.LENGTH_SHORT).show();
		}
	}

	@Override
	public void onConnected(Bundle arg0) {
		// TODO Auto-generated method stub
		Toast.makeText(this, "Connected", Toast.LENGTH_SHORT).show();
		Location location = mLocationClient.getLastLocation();
		LatLng latLng = new LatLng(location.getLatitude(), location.getLongitude());
		CameraUpdate cameraUpdate = CameraUpdateFactory.newLatLngZoom(latLng, 19);
		map.animateCamera(cameraUpdate);
		
		int radius = getIntent().getIntExtra("radius", 20);
		Toast.makeText(this, "Go to the outside of the area : " + radius + "m", Toast.LENGTH_SHORT).show();
		addProximityAlert(latLng,  radius);
	}
	
	@Override
	public void onDisconnected() {
		// TODO Auto-generated method stub
		Toast.makeText(this, "Disconnected. Please re-connect.",
	            Toast.LENGTH_SHORT).show();
	}

	
	// For LocationListener
	@Override
	public void onLocationChanged(Location location) {
		// TODO Auto-generated method stub
		LatLng latLng = new LatLng(location.getLatitude(), location.getLongitude());
	    CameraUpdate cameraUpdate = CameraUpdateFactory.newLatLngZoom(latLng, 19);
	    map.animateCamera(cameraUpdate);
	    map.addMarker(new MarkerOptions()
	    	.position(latLng)
	    	.icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_AZURE))
	    	.title("Here"));
	}

	@Override
	public void onStatusChanged(String provider, int status, Bundle extras) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onProviderEnabled(String provider) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onProviderDisabled(String provider) {
		// TODO Auto-generated method stub
		
	}
	
	class ProximityAlertReceiver extends BroadcastReceiver{
		String key = LocationManager.KEY_PROXIMITY_ENTERING;

		@Override
		public void onReceive(Context context, Intent intent) {
			// TODO Auto-generated method stub
			if(intent.getBooleanExtra(key,false)){
				isOutside = false;
			} else {
				isOutside = true;
				Toast.makeText(getBaseContext(), "Well done!!", 
						Toast.LENGTH_SHORT).show();
			}
		}
	}
}
