package com.luoye.localdlfcn;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.luoye.localdlfcn.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'localdlfcn' library on application startup.
    static {
        System.loadLibrary("localdlfcn");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(test());
    }

    /**
     * A native method that is implemented by the 'localdlfcn' native library,
     * which is packaged with this application.
     */
    public native String test();
}