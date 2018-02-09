package co.getmade.spark.plugins;

import android.os.Process;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.URL;

public class Fetch implements Runnable {
    private String url;
    private String filePath;

    @Override
    public void run() {
        android.os.Process.setThreadPriority(Process.THREAD_PRIORITY_BACKGROUND);

        try {
            File file = new File(filePath);
            if(!file.exists()) {
                file.getParentFile().mkdirs();
                
                URL webURL = new URL(url);
                InputStream in = new BufferedInputStream(webURL.openStream());
                FileOutputStream out = new FileOutputStream(filePath);

                byte[] buf = new byte[1024];
                int n = 0;
                while (-1 != (n = in.read(buf))) {
                    out.write(buf, 0, n);
                }

                out.flush();
                out.close();
                in.close();
            }
        }
        catch(Exception e) {
            System.out.println(e);
        }
    }

    Fetch(String filePath, String url) {
        this.url = url;
        this.filePath = filePath;
    }
}