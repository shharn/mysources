package com.example.alarmretry;

import java.util.Calendar;

import android.app.Activity;
import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;
import android.widget.ToggleButton;

public class AlarmConfiguration extends Activity{
	private	TimePicker mTime;
	private TextView ringtoneTitle;
	private AlarmClass alarm;
	private CheckBox repeatWeekly;
	private AlarmDBHelper db = new AlarmDBHelper(this);
	private SeekBar skVolume;
	private SeekBar skRadius;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_config);
        alarm = new AlarmClass();
    	mTime = (TimePicker) findViewById(R.id.timepicker);
 
    	ringtoneTitle = (TextView) findViewById(R.id.ringtone_title);
    	repeatWeekly = (CheckBox) findViewById(R.id.repeatweekly);
    	skVolume = (SeekBar) findViewById(R.id.volume);
    	skRadius = (SeekBar) findViewById(R.id.radius);
    	
    	
        long alarmId = getIntent().getLongExtra("id", -1);
        if(alarmId != -1){
        	alarm = db.getAlarm(alarmId);
        	// get the time-picker instance and set the listener
        
        	mTime.setCurrentHour(alarm.timeHour);
        	mTime.setCurrentMinute(alarm.timeMinute);
        	
        	((ToggleButton)findViewById(R.id.sunday)).setChecked(alarm.getRepeatingDay(alarm.SUNDAY));
        	((ToggleButton)findViewById(R.id.monday)).setChecked(alarm.getRepeatingDay(alarm.MONDAY));
        	((ToggleButton)findViewById(R.id.tuesday)).setChecked(alarm.getRepeatingDay(alarm.TUESDAY));
        	((ToggleButton)findViewById(R.id.wednesday)).setChecked(alarm.getRepeatingDay(alarm.WEDNESDAY));
        	((ToggleButton)findViewById(R.id.thursday)).setChecked(alarm.getRepeatingDay(alarm.THURSDAY));
        	((ToggleButton)findViewById(R.id.friday)).setChecked(alarm.getRepeatingDay(alarm.FRIDAY));
        	((ToggleButton)findViewById(R.id.saturday)).setChecked(alarm.getRepeatingDay(alarm.SATURDAY));
        	
        	ringtoneTitle.setText(RingtoneManager.getRingtone(this, alarm.alarmTone).getTitle(this));
        	
        	repeatWeekly.setChecked(alarm.isRepeat);
        	
        	skVolume.setProgress(alarm.volume);
        	skRadius.setProgress(alarm.radius);
        
        } else {
        	alarm = new AlarmClass();
        }
        
        skVolume.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				// TODO Auto-generated method stub
				alarm.volume = progress;
			}
		});
        
        
        skRadius.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
			
			@Override
			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}
			
			@Override
			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				// TODO Auto-generated method stub
				alarm.radius = progress;
			}
		});
        
        // OnClickListener for ringtone layout
        LinearLayout layout = (LinearLayout) findViewById(R.id.ringtone_layout);
        layout.setOnClickListener(new View.OnClickListener(){
        	@Override
        	public void onClick(View v){
        		Intent intent = new Intent(RingtoneManager.ACTION_RINGTONE_PICKER);
        		startActivityForResult(intent, 1);
        	}
        });
        
       
    }
    
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
    	super.onActivityResult(requestCode, resultCode, data);
    	
    	if(resultCode == RESULT_OK){
    		switch(requestCode){
    		case 1:
    			
    			// Get Uri of ringtone
    			Uri title = data.getParcelableExtra(RingtoneManager.EXTRA_RINGTONE_PICKED_URI);
    			
    			// Set Uri for ringtone
    			alarm.alarmTone = title;
    			
    			
    			// Set the text to the selected ringtone title
    			String strTitle;
    			strTitle = RingtoneManager.getRingtone(this, title).getTitle(this);
    			ringtoneTitle.setText(strTitle);
    		}
    	}
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.config_activity_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.actionbar_ok) {
        	if(ringtoneTitle.getText().toString().compareTo("Select Ringtone") == 0)
        	{
        		Toast.makeText(this, "Should select ringtone", Toast.LENGTH_SHORT).show();
        		return super.onOptionsItemSelected(item);
        	}
        	
        	
        	createNewAlarmInformation();
        	       	
        	//AlarmManagerHelper.cancelAlarms(this);
        	
        	// save to database
        	if(alarm.id < 0)
        		db.createAlarmClass(alarm);
        	else
        		db.updateAlarmClass(alarm);
        	
        	// Update the alarm services to newest alarm list
        	AlarmManagerHelper.setAlarms(this);
        	
        	setResult(RESULT_OK);
        	finish(); 
        	
        } else if(id == R.id.actionbar_cancel){
        	// cancel
        	finish();
        }
       
        return super.onOptionsItemSelected(item);
    }
    
    private void createNewAlarmInformation(){
    	// Save the configuration to system
    	alarm.timeHour = mTime.getCurrentHour();
    	alarm.timeMinute = mTime.getCurrentMinute();
    	alarm.setRepeatingDay(alarm.SUNDAY, ((ToggleButton)findViewById(R.id.sunday)).isChecked());
    	alarm.setRepeatingDay(alarm.MONDAY, ((ToggleButton)findViewById(R.id.monday)).isChecked());
    	alarm.setRepeatingDay(alarm.TUESDAY, ((ToggleButton)findViewById(R.id.tuesday)).isChecked());
    	alarm.setRepeatingDay(alarm.WEDNESDAY, ((ToggleButton)findViewById(R.id.wednesday)).isChecked());
    	alarm.setRepeatingDay(alarm.THURSDAY, ((ToggleButton)findViewById(R.id.thursday)).isChecked());
    	alarm.setRepeatingDay(alarm.FRIDAY, ((ToggleButton)findViewById(R.id.friday)).isChecked());
    	alarm.setRepeatingDay(alarm.SATURDAY, ((ToggleButton)findViewById(R.id.saturday)).isChecked());
    	alarm.isRepeat = repeatWeekly.isChecked();
    	alarm.isEnabled = true; 
    }
}
