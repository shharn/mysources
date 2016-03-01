package com.example.alarmretry;

import android.net.Uri;

public class AlarmClass {
	public static final int SUNDAY = 0;
	public static final int MONDAY = 1;
	public static final int TUESDAY = 2;
	public static final int WEDNESDAY = 3;
	public static final int THURSDAY = 4;
	public static final int FRIDAY = 5;
	public static final int SATURDAY = 6;
	
	public long id = -1;
	public int timeHour;
	public int timeMinute;
	private boolean repeatingDays[];
	public boolean isRepeat;
	public Uri alarmTone;
	public boolean isEnabled;
	public int volume;
	public int radius;
	
	public AlarmClass() {
		repeatingDays = new boolean[7];
		volume = 7;
		radius = 20;
	}
	
	public void setRepeatingDay(int dayOfWeek, boolean value) {
		repeatingDays[dayOfWeek] = value;
	}
	
	public boolean getRepeatingDay(int dayOfWeek) {
		return repeatingDays[dayOfWeek];
	}
}
