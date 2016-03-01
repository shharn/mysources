package com.example.alarmretry;

import java.util.Calendar;
import java.util.List;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class AlarmManagerHelper extends BroadcastReceiver{
	public static final String ID = "id";
	public static final String NAME = "name";
	public static final String TIME_HOUR = "timeHour";
	public static final String TIME_MINUTE = "timeMinute";
	public static final String TONE = "tone";
	public static final String VOLUME = "volume";
	public static final String RADIUS = "radius";
	
	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		setAlarms(context);
	}
	
	public static void setAlarms(Context context){
		cancelAlarms(context);
		
		AlarmDBHelper db = new AlarmDBHelper(context);
		
		List<AlarmClass> alarms = db.getAlarms();
		if(alarms != null){
			for(AlarmClass alarm : alarms){
				if(alarm.isEnabled){
					PendingIntent pIntent = createPendingIntent(context, alarm);
				
					Calendar calendar = Calendar.getInstance();
					calendar.set(Calendar.HOUR_OF_DAY, alarm.timeHour);
					calendar.set(Calendar.MINUTE, alarm.timeMinute);
					calendar.set(Calendar.SECOND, 00);
				
					final int currentDay = Calendar.getInstance().get(Calendar.DAY_OF_WEEK);
					final int currentHour = Calendar.getInstance().get(Calendar.HOUR_OF_DAY);
					final int currentMinute = Calendar.getInstance().get(Calendar.MINUTE);
					boolean alarmSet = false;
					
					//First check if it's later in the week
					for (int dayOfWeek = Calendar.SUNDAY; dayOfWeek <= Calendar.SATURDAY; ++dayOfWeek) {
						if (alarm.getRepeatingDay(dayOfWeek - 1) && dayOfWeek >= currentDay &&
								!(dayOfWeek == currentDay && alarm.timeHour < currentDay) &&
								!(dayOfWeek == currentDay && alarm.timeHour == currentDay && alarm.timeMinute <= currentDay)) {
							calendar.set(Calendar.DAY_OF_WEEK, dayOfWeek);
							
							setAlarm(context, calendar, pIntent);
							alarmSet = true;
							break;
						}
					}
					
					//Else check if it's earlier in the week
					if (!alarmSet) {
						for (int dayOfWeek = Calendar.SUNDAY; dayOfWeek <= Calendar.SATURDAY; ++dayOfWeek) {
							if (alarm.getRepeatingDay(dayOfWeek - 1) && dayOfWeek <= currentDay && alarm.isRepeat) {
								calendar.set(Calendar.DAY_OF_WEEK, dayOfWeek);
								calendar.add(Calendar.WEEK_OF_YEAR, 1);
								
								setAlarm(context, calendar, pIntent);
								alarmSet = true;
								break;
							}
						}
					}
				}
			}
		}
	}
	
	public static void setAlarm(Context context, Calendar calendar, PendingIntent pIntent){
		AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
		alarmManager.set(AlarmManager.RTC_WAKEUP, calendar.getTimeInMillis(), pIntent);
	}
	
	public static void cancelAlarms(Context context){
		AlarmDBHelper db = new AlarmDBHelper(context);
		
		List<AlarmClass> alarms = db.getAlarms();
		
		if(alarms  != null){
			for(AlarmClass alarm : alarms){
				if(alarm.isEnabled){
					PendingIntent pIntent = createPendingIntent(context, alarm);
					
					AlarmManager alarmManager = (AlarmManager) context.getSystemService(Context.ALARM_SERVICE);
					alarmManager.cancel(pIntent);
				}
			}
		}
	}
	
	private static PendingIntent createPendingIntent(Context context, AlarmClass alarm){
		Intent intent = new Intent(context, AlarmService.class);
		intent.putExtra(ID, alarm.id);
		intent.putExtra(TONE, alarm.alarmTone.toString());
		//intent.putExtra(VOLUME, (short)alarm.volume);
		intent.putExtra(RADIUS, alarm.radius);
		
		return PendingIntent.getService(context, (int) alarm.id, intent, PendingIntent.FLAG_UPDATE_CURRENT);
	}

}
