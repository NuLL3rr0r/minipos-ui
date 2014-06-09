package com.rahpooyanco.minipos;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;
import java.lang.Exception;

public class Android extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static final String TAG = "[Android Interface / com.rahpooyanco.minipos.Android]";

    private static Android m_instance;

    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_notificationBuilder;

    public Android()
    {
        m_instance = this;

        Log.v(TAG, "Android interface successfully initialized!");
    }

    public static boolean release()
    {
        try {
            if (m_instance != null) {
                m_instance = null;

                Log.v(TAG, "Android interface successfully released!");
            }
        }

        catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        return true;
    }

    public static boolean isInitialized()
    {
        return m_instance != null ? true : false;
    }

    public static boolean notify(final CharSequence title, final CharSequence text, final int id)
    {
        try {
            if (m_notificationManager == null) {
                m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
                m_notificationBuilder = new Notification.Builder(m_instance);
                m_notificationBuilder.setSmallIcon(R.drawable.icon);
            }

            m_notificationBuilder.setContentTitle(title);
            m_notificationBuilder.setContentText(text);
            m_notificationManager.notify(id, m_notificationBuilder.build());
        }

        catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        return true;
    }

    public static boolean showToast(final CharSequence text, final int duration)
    {
        try {
            m_instance.runOnUiThread(new Runnable() {
                public void run() {
                    Toast toast = Toast.makeText(m_instance, text, duration);
                    toast.show();
                }
            });
        }

        catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        return true;
    }
}

