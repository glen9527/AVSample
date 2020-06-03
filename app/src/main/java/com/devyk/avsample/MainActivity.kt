package com.devyk.avsample

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import com.devyk.fdkaac_audio_encode.sample.AudioRecordActivty
import com.devyk.fdkaac_audio_encode.sample.FDKAACEncodeActivty
import com.devyk.ikavedit.base.BaseActivity

class MainActivity : BaseActivity() {
    override fun initListener() {
    }

    override fun initData() {
    }

    override fun init() {
        checkPermission()
    }

    override fun getLayoutId(): Int = R.layout.activity_main


    /**
     * 音频采集
     */
    fun AudioCapture(view: View) {

        startActivity(Intent(this, AudioRecordActivty::class.java))

    }

    /**
     * FDK-AAC 音频编码
     */
    fun fdkaac_encode(view: View) {
        startActivity(Intent(this, FDKAACEncodeActivty::class.java))

    }
}
