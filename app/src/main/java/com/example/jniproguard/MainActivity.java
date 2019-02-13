package com.example.jniproguard;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.jnilibrary.JniUtils;

public class MainActivity extends AppCompatActivity {

    private int mClicks;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(JniUtils.stringFromJNI());

        final Button btn = findViewById(R.id.sample_btn);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mClicks = JniUtils.calculateByJNI(mClicks);
                btn.setText("Clicked " + mClicks + " times");
            }
        });
    }
}
