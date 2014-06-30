package com.rahpooyanco.minipos;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;
import java.lang.Exception;

import cn.newpos.tech.api.dao.DeviceDao;
import cn.newpos.tech.api.dao.EventListener.HeadSetStateListener;
import cn.newpos.tech.api.dao.impl.DeviceImpl;

public class Android extends org.qtproject.qt5.android.bindings.QtActivity
{
    private static final String TAG = "[Android Interface / com.rahpooyanco.minipos.Android]";

    private static Android s_instance;

    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_notificationBuilder;

    private DeviceDao m_deviceDao;

    public static native void onHeadSetStateChanged(int state);

    public static boolean release()
    {
        try {
            if (s_instance != null) {
                s_instance = null;

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
        Log.v(TAG, "isInitialized");

        return s_instance != null ? true : false;
    }

    public static boolean notify(final CharSequence title, final CharSequence text, final int id)
    {
        Log.v(TAG, "notify");

        try {
            if (m_notificationManager == null) {
                m_notificationManager = (NotificationManager)s_instance.getSystemService(Context.NOTIFICATION_SERVICE);
                m_notificationBuilder = new Notification.Builder(s_instance);
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
        Log.v(TAG, "showToast");

        try {
            s_instance.runOnUiThread(new Runnable() {
                public void run() {
                    Toast toast = Toast.makeText(s_instance, text, duration);
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

    public Android()
    {
        s_instance = this;

        Log.v(TAG, "Android interface successfully initialized!");
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        m_deviceDao = new DeviceImpl(this);
        m_deviceDao.getHeadSetStateListener(new HeadSetStateListener() {
            @Override
            public void getHeadSetState(int state) {
                onHeadSetStateChanged(state);
            }
        });
    }
}

