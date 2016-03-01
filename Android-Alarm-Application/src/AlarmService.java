package com.example.alarmretry;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;


public class AlarmService extends Service{
public static String TAG = AlarmService.class.getSimpleName();
	
	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}
	
	@Override
	public int onStartCommand(Intent intent, int flags, int startId){
		
		
			Intent alarmIntent = new Intent(getBaseContext(), AlarmMapActivity.class);
			alarmIntent.addFlags(intent.FLAG_ACTIVITY_NEW_TASK);
			alarmIntent.putExtras(intent);
			getApplication().startActivity(alarmIntent);
		
		//AlarmManagerHelper.setAlarms(this);
		
		return super.onStartCommand(intent, flags, startId);
	}

}
