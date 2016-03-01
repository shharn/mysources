package com.example.alarmretry;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;


public class FirstActivity extends ListActivity {
	
	private AlarmDBHelper dbHelper = new AlarmDBHelper(this);
	private AlarmListAdapter adapter;
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_ACTION_BAR);
        setContentView(R.layout.first_activity);
        //dbHelper.getWritableDatabase().execSQL(dbHelper.SQL_DROP_ALARM);
        adapter = new AlarmListAdapter(this, dbHelper.getAlarms());
              
        setListAdapter(adapter);
        
    }
    
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.first_activity_menu, menu);
		return true;
	}
	
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.actionbar_add) {
        	startConfigurationActivity(-1);
        } 
        
        return super.onOptionsItemSelected(item);
    }
    
    public void startConfigurationActivity(long id){
    	Intent intent = new Intent(this, AlarmConfiguration.class);
    	intent.putExtra("id", id);
    	startActivityForResult(intent, 0);
    }
    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
    	super.onActivityResult(requestCode, resultCode, data);
    	
    	if(resultCode == RESULT_OK){
    		adapter.setAlarms(dbHelper.getAlarms());
    		adapter.notifyDataSetChanged();
    	}
    }
    
    public void removeAlarm(long id){
    	final long alarmId = id;
    	AlertDialog.Builder dialog = new AlertDialog.Builder(this);
    	dialog.setMessage("Do you want to remove?")
    	.setTitle("Remove?")
    	.setCancelable(true)
    	.setNegativeButton("Cancel", null)
    	.setPositiveButton("OK", new DialogInterface.OnClickListener(){
    		public void onClick(DialogInterface dlgInterface, int which){
    			AlarmManagerHelper.cancelAlarms(FirstActivity.this);
    			dbHelper.removeAlarm(alarmId);
    			adapter.setAlarms(dbHelper.getAlarms());
    			adapter.notifyDataSetChanged();
    			AlarmManagerHelper.setAlarms(FirstActivity.this);
    		}
    	}).show();
    }
    
    public void setAlarmEnabled(long id, boolean isEnabled) {
		AlarmManagerHelper.cancelAlarms(this);
		
		AlarmClass obj = dbHelper.getAlarm(id);
		obj.isEnabled = isEnabled;
		dbHelper.updateAlarmClass(obj);
		
		AlarmManagerHelper.setAlarms(this);
		
    }
}
