package org.andiacoincore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class AndiacoinQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File andiacoinDir = new File(getFilesDir().getAbsolutePath() + "/.andiacoin");
        if (!andiacoinDir.exists()) {
            andiacoinDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
