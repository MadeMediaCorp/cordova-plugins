package co.getmade.spark.plugins;

import android.content.Context;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class ImageFetcher extends CordovaPlugin {
    private String action = null;
    private CallbackContext callbackContext = null;
    private JSONArray images = null;
    private String campaign = null;

    private static final int MAX_POOL = 10;
    private static final String invalidChars = "[^\\w\\s]";

    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        this.images = args.getJSONArray(0);
        this.campaign = args.getString(1);

        this.callbackContext = callbackContext;
        this.action = action;

        return decideCall();
    }

    private boolean decideCall() {
        if(action.equals("download")) {
            download(callbackContext);

            return true;
        }
        return false;
    }


    private void download(CallbackContext callbackContext) {
        Context context = cordova.getActivity().getApplicationContext();

        try {
            ExecutorService pool = Executors.newFixedThreadPool(MAX_POOL);

            JSONObject obj;
            String url, value, filePath;

            for(int j = 0; j < images.length(); j++) {
                obj = images.getJSONObject(j);

                url = obj.getString("img");
                value = obj.getString("value").replaceAll(invalidChars, "");

                filePath = context.getFilesDir().getAbsolutePath() + "/pics/" + campaign + "/" + value + ".png";

                pool.submit(new Fetch(filePath, url));

                obj.put("img", filePath);
                images.put(j, obj);
            }

            pool.shutdown();
            pool.awaitTermination(Long.MAX_VALUE, TimeUnit.MILLISECONDS);

            callbackContext.success(images.toString());
        }
        catch(Exception e) {
            callbackContext.error(e.toString());
        }
    }
}
