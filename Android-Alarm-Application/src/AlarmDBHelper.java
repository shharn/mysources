package com.example.alarmretry;

import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.net.Uri;
import android.provider.BaseColumns;

public class AlarmDBHelper extends SQLiteOpenHelper implements BaseColumns{
	public static final int DATABASE_VERSION = 1;
    public static final String DATABASE_NAME = "alarm5.db";
    public static final String SQL_TABLE_NAME = "alarm";
    public static final String DELIMETER = "|";
    
    
	public static final String TABLE_NAME = "alarm";
	public static final String COLUMN_NAME_ALARM_TIME_HOUR = "hour";
	public static final String COLUMN_NAME_ALARM_TIME_MINUTE = "minute";
	public static final String COLUMN_NAME_ALARM_REPEAT_DAYS = "days";
	public static final String COLUMN_NAME_ALARM_REPEAT_WEEKLY = "weekly";
	public static final String COLUMN_NAME_ALARM_TONE = "tone";
	public static final String COLUMN_NAME_ALARM_ENABLED = "enabled";
	public static final String COLUMN_NAME_ALARM_VOLUME = "volume";
	public static final String COLUMN_NAME_ALARM_RADIUS = "radius";
    
    private static final String SQL_CREATE_ALARM = "CREATE TABLE " + SQL_TABLE_NAME + " (" +
    		_ID + " INTEGER PRIMARY KEY AUTOINCREMENT," +
			COLUMN_NAME_ALARM_TIME_HOUR + " INTEGER," +
			COLUMN_NAME_ALARM_TIME_MINUTE + " INTEGER," +
			COLUMN_NAME_ALARM_REPEAT_DAYS + " TEXT," +
			COLUMN_NAME_ALARM_REPEAT_WEEKLY + " BOOLEAN," +
			COLUMN_NAME_ALARM_TONE + " TEXT," +
			COLUMN_NAME_ALARM_ENABLED + " BOOLEAN," + 
			COLUMN_NAME_ALARM_VOLUME + " INTEGER," +
			COLUMN_NAME_ALARM_RADIUS + " INTEGER" + " )";
    
    public static final String SQL_DROP_ALARM = 
    		"DROP TABLE IF EXISTS " + TABLE_NAME;
    
	public AlarmDBHelper(Context context) {
		super(context, DATABASE_NAME, null, DATABASE_VERSION);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		// TODO Auto-generated method stub
		db.execSQL(SQL_CREATE_ALARM);
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		// TODO Auto-generated method stub
		db.execSQL(SQL_DROP_ALARM);
		onCreate(db);
	}
	
	private AlarmClass getAlarmClass(Cursor c){
		AlarmClass obj = new AlarmClass();
		obj.id = c.getLong(c.getColumnIndex(_ID));
		obj.timeHour = c.getInt(c.getColumnIndex(COLUMN_NAME_ALARM_TIME_HOUR));
		obj.timeMinute = c.getInt(c.getColumnIndex(COLUMN_NAME_ALARM_TIME_MINUTE));
		obj.isRepeat = c.getInt(c.getColumnIndex(COLUMN_NAME_ALARM_REPEAT_WEEKLY)) == 0 ? false : true;
		obj.alarmTone = c.getString(c.getColumnIndex(COLUMN_NAME_ALARM_TONE)) != "" ? 
				Uri.parse(c.getString(c.getColumnIndex(COLUMN_NAME_ALARM_TONE))) : null;
		obj.isEnabled = c.getInt(c.getColumnIndex(COLUMN_NAME_ALARM_ENABLED)) == 0 ? false : true;
		obj.volume = c.getInt(c.getColumnIndex(COLUMN_NAME_ALARM_VOLUME));
		obj.radius = c.getInt(c.getColumnIndex(COLUMN_NAME_ALARM_RADIUS));
		
		//String[] dayOfWeeks = c.getString(c.getColumnIndex(COLUMN_NAME_ALARM_REPEAT_DAYS)).split(DELIMETER);
		StringTokenizer strToken = new StringTokenizer(c.getString(c.getColumnIndex(COLUMN_NAME_ALARM_REPEAT_DAYS)), "|");
		
		int count=0;
		while(strToken.hasMoreTokens()){
			String str =  strToken.nextToken();
			obj.setRepeatingDay(count++, str.compareTo("false") == 0 ? false : true);
		}
		
		return obj;
	}

	public long createAlarmClass(AlarmClass obj){
		ContentValues values = new ContentValues();
		values.put(COLUMN_NAME_ALARM_TIME_HOUR, obj.timeHour);
        values.put(COLUMN_NAME_ALARM_TIME_MINUTE, obj.timeMinute);
        values.put(COLUMN_NAME_ALARM_REPEAT_WEEKLY, obj.isRepeat);
        values.put(COLUMN_NAME_ALARM_TONE, obj.alarmTone != null ? obj.alarmTone.toString() : "");
        values.put(COLUMN_NAME_ALARM_ENABLED, obj.isEnabled);
        values.put(COLUMN_NAME_ALARM_VOLUME, obj.volume);
        values.put(COLUMN_NAME_ALARM_RADIUS, obj.radius);
        
        String repeatingDays = "";
        for (int i = 0; i < 7; ++i) {
        	repeatingDays += obj.getRepeatingDay(i) + DELIMETER;
        }
        values.put(COLUMN_NAME_ALARM_REPEAT_DAYS, repeatingDays);
        
        return getWritableDatabase().insert(TABLE_NAME, null, values);
	}
	
	public long updateAlarmClass(AlarmClass obj){
		ContentValues values = new ContentValues();
		values.put(COLUMN_NAME_ALARM_TIME_HOUR, obj.timeHour);
        values.put(COLUMN_NAME_ALARM_TIME_MINUTE, obj.timeMinute);
        values.put(COLUMN_NAME_ALARM_REPEAT_WEEKLY, obj.isRepeat);
        values.put(COLUMN_NAME_ALARM_TONE, obj.alarmTone != null ? obj.alarmTone.toString() : "");
        values.put(COLUMN_NAME_ALARM_ENABLED, obj.isEnabled);
        values.put(COLUMN_NAME_ALARM_VOLUME, obj.volume);
        values.put(COLUMN_NAME_ALARM_RADIUS, obj.radius);
        
        String repeatingDays = "";
        for (int i = 0; i < 7; ++i) {
        	repeatingDays += obj.getRepeatingDay(i) + DELIMETER;
        }
        values.put(COLUMN_NAME_ALARM_REPEAT_DAYS, repeatingDays);
        
        return getWritableDatabase().update(TABLE_NAME, values, _ID + " = ?", new String[] { String.valueOf(obj.id) });
	}
	
	public AlarmClass getAlarm(long id){
		SQLiteDatabase db = this.getReadableDatabase();
		
		String query = "SELECT * FROM " + TABLE_NAME + " WHERE " + _ID + " = " + id;
		
		Cursor c = db.rawQuery(query, null);
		
		if(c.moveToFirst()){
			return getAlarmClass(c);
		}
		
		return null;
	}
	
	public List<AlarmClass> getAlarms(){
		SQLiteDatabase db = this.getReadableDatabase();
		
		String query = "SELECT * FROM " + TABLE_NAME;
		
		Cursor c = db.rawQuery(query, null);
		
		List<AlarmClass> alarmList = new ArrayList<AlarmClass>();
		
		while(c.moveToNext())
			alarmList.add(getAlarmClass(c));
		
		if(alarmList.isEmpty())
			return null;
		else
			return alarmList;
	}
	
	public int removeAlarm(long id){
		return getWritableDatabase().delete(TABLE_NAME, _ID + " = ?", new String[] { String.valueOf(id) });
	}
}
