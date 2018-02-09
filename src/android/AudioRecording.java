package co.getmade.spark.plugins;

import android.Manifest;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.media.MediaRecorder;
import android.support.v4.app.NotificationCompat;
import android.content.res.Resources;
import android.graphics.drawable.Drawable;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;

import java.io.File;
import java.io.IOException;

public class AudioRecording extends CordovaPlugin {
    private MediaRecorder recorder = null;
    private String filepath = null;
    private String action = null;
    private String alertTitle = null;
    private String alertDescription = null;
    private CallbackContext callbackContext = null;

    private static final String [] permissions = {
        Manifest.permission.RECORD_AUDIO, Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE
    };
    private static final int AUDIO_REQ_CODE = 1;
    private static final int ANDROID_AUDIO_PUSH_ID = 152453253;

    @Override
    public void onRequestPermissionResult(int requestCode, String[] permissions,
                                          int[] grantResults) throws JSONException {
        for(int r:grantResults)
        {
            if(r == PackageManager.PERMISSION_DENIED)
            {
                this.callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.ERROR, "PERMISSION DENIED"));
                return;
            }
        }
        switch(requestCode)
        {
            case AUDIO_REQ_CODE:
                decideCall();
                break;
        }
    }

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        this.alertTitle = args.getString(0);
        this.alertDescription = args.getString(1);
        this.callbackContext = callbackContext;
        this.action = action;

        System.out.println(action);

        if(cordova.hasPermission(permissions[0]) && cordova.hasPermission(permissions[1]) && cordova.hasPermission(permissions[2])) {
            return decideCall();
        }
        else {
            cordova.requestPermissions(this, AUDIO_REQ_CODE, permissions);

            return true;
        }
    }

    private boolean decideCall() {
        if(action.equals("start")) {
            start(callbackContext);

            return true;
        }
        else if(action.equals("pause")) {
            pause(callbackContext);

            return true;
        }
        else if(action.equals("resume")) {
            resume(callbackContext);

            return true;
        }
        else if(action.equals("stop")) {
            stop(callbackContext);

            return true;
        }
        else if(action.equals("get")) {
            get(callbackContext);

            return true;
        }
        else if(action.equals("del")) {
            del(callbackContext);

            return true;
        }
        return false;
    }

    private void sayIsRecording() {
        Context context = cordova.getActivity().getApplicationContext();

        String title = this.alertTitle;
        String description = this.alertDescription;

        Resources activityRes = cordova.getActivity().getResources();
        int microphoneId = activityRes.getIdentifier("ic_stat_microphone", "drawable", cordova.getActivity().getPackageName());

        NotificationCompat.Builder notBuild = new NotificationCompat.Builder(context)
                .setContentTitle(title)
                .setContentText(description)
                .setSmallIcon(microphoneId)
                .setWhen(System.currentTimeMillis())
                .setContentIntent(PendingIntent.getActivity(context, 0, cordova.getActivity().getIntent().setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP), PendingIntent.FLAG_CANCEL_CURRENT));

        Notification notObj = notBuild.build();
        notObj.defaults |= Notification.DEFAULT_LIGHTS;
        notObj.flags |= Notification.FLAG_ONGOING_EVENT;
        notObj.tickerText = title+"\n"+description;
        NotificationManager manager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);

        manager.notify(ANDROID_AUDIO_PUSH_ID, notObj);
    }

    private void sayIsDoneRecording() {
        Context context = cordova.getActivity().getApplicationContext();

        NotificationManager manager = (NotificationManager) context.getSystemService(Context.NOTIFICATION_SERVICE);
        manager.cancel(ANDROID_AUDIO_PUSH_ID);
    }

    private void start(CallbackContext callbackContext) {
        Context context = cordova.getActivity().getApplicationContext();
        String file = "voice.mp4";
        filepath = context.getFilesDir().getAbsolutePath() + "/" + file;

        recorder = new MediaRecorder();
        recorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        recorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
        recorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
        recorder.setAudioSamplingRate(8000);
        recorder.setAudioEncodingBitRate(25000);
        recorder.setAudioChannels(1);
        recorder.setOutputFile(filepath);

        try {
            recorder.prepare();
        }
        catch(IOException e) {
            callbackContext.error(e.toString());
        }

        recorder.start();
        sayIsRecording();

        System.out.println("started recording to: "+filepath);

        callbackContext.success(filepath);
    }

    //TODO - API 24 (Current 21)
    private void pause(CallbackContext callbackContext) {
        callbackContext.success("NOT IMPLEMENTED");
    }
    //TODO - API 24 (Current 21)
    private void resume(CallbackContext callbackContext) {
        callbackContext.success("NOT IMPLEMENTED");
    }
    private void stop(CallbackContext callbackContext) {
        if(recorder != null) {
            recorder.stop();
            recorder.release();
            recorder = null;
        }

        sayIsDoneRecording();

        System.out.println("stopped recording");

        callbackContext.success("stopped");
    }
    private void get(CallbackContext callbackContext) {
        callbackContext.success(filepath);
    }
    private void del(CallbackContext callbackContext) {
        File file = new File(filepath);
        boolean deleted = file.delete();
        if(deleted) {
            callbackContext.success("deleted");
        }
        else {
            callbackContext.error("failed to delete");
        }
    }
}
