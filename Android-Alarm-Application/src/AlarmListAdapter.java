package com.example.alarmretry;

import java.util.List;

import android.content.Context;
import android.graphics.Color;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.ToggleButton;
import android.widget.CompoundButton.OnCheckedChangeListener;

public class AlarmListAdapter extends BaseAdapter{
	private Context mContext;
	private List<AlarmClass> mAlarms;
		
	public AlarmListAdapter(Context context, List<AlarmClass> alarms){
		mContext = context;
		mAlarms = alarms;
	}

	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		if(mAlarms != null){
			return mAlarms.size();
		}
		return 0;
	}

	@Override
	public Object getItem(int position) {
		// TODO Auto-generated method stub
		if(mAlarms != null){
			return mAlarms.get(position);
		}
		return null;
	}

	@Override
	public long getItemId(int position) {
		if(mAlarms != null){
			return mAlarms.get(position).id;
		}
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		
		if(convertView == null){
			LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(R.layout.list_item, parent, false);
		}
		
		AlarmClass obj = (AlarmClass) getItem(position);
		
		TextView textTime = (TextView) convertView.findViewById(R.id.alarm_time);
		textTime.setText(String.format("%02d : %02d", obj.timeHour, obj.timeMinute));
		
		((TextView) convertView.findViewById(R.id.alarm_item_sunday)).setTextColor(
				(obj.getRepeatingDay(AlarmClass.SUNDAY)) ? Color.GREEN : Color.BLACK);
		((TextView) convertView.findViewById(R.id.alarm_item_monday)).setTextColor(
				(obj.getRepeatingDay(AlarmClass.MONDAY)) ? Color.GREEN : Color.BLACK);
		((TextView) convertView.findViewById(R.id.alarm_item_tuesday)).setTextColor(
				(obj.getRepeatingDay(AlarmClass.TUESDAY)) ? Color.GREEN : Color.BLACK);
		((TextView) convertView.findViewById(R.id.alarm_item_wednesday)).setTextColor(
				(obj.getRepeatingDay(AlarmClass.WEDNESDAY)) ? Color.GREEN : Color.BLACK);
		((TextView) convertView.findViewById(R.id.alarm_item_thursday)).setTextColor(
				(obj.getRepeatingDay(AlarmClass.THURSDAY)) ? Color.GREEN : Color.BLACK);
		((TextView) convertView.findViewById(R.id.alarm_item_friday)).setTextColor(
				(obj.getRepeatingDay(AlarmClass.FRIDAY)) ? Color.GREEN : Color.BLACK);
		((TextView) convertView.findViewById(R.id.alarm_item_saturday)).setTextColor(
				(obj.getRepeatingDay(AlarmClass.SATURDAY)) ? Color.GREEN : Color.BLACK);
		
		ToggleButton onoff = (ToggleButton) convertView.findViewById(R.id.toggleButton1);
		onoff.setChecked(obj.isEnabled);
		onoff.setTag(Long.valueOf(obj.id));
		onoff.setOnCheckedChangeListener(new OnCheckedChangeListener(){
			@Override
			public void onCheckedChanged(CompoundButton buttonView, boolean isChecked){
				((FirstActivity)mContext).setAlarmEnabled(((Long) buttonView.getTag()).longValue(), isChecked);
			}
		});
				
		convertView.setTag(Long.valueOf(obj.id));
		convertView.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				((FirstActivity)mContext).startConfigurationActivity(((Long) v.getTag()).longValue());
			}
		});
		
		convertView.setOnLongClickListener(new View.OnLongClickListener() {
			
			@Override
			public boolean onLongClick(View v) {
				// TODO Auto-generated method stub
				((FirstActivity)mContext).removeAlarm(((Long) v.getTag()).longValue());
				return true;
			}
		});
		
		return convertView;
	}
	
	public void setAlarms(List<AlarmClass> alarms){
		mAlarms = alarms;
	}

}
