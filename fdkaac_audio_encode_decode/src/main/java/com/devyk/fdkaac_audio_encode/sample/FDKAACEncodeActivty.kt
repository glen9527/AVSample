package com.devyk.fdkaac_audio_encode.sample

import android.os.Handler
import android.os.SystemClock
import android.util.Log
import android.view.View
import com.devyk.fdkaac_audio_encode.FDKAACEncode
import com.devyk.fdkaac_audio_encode.R
import com.devyk.ikavedit.audio.AudioCapture
import com.devyk.ikavedit.base.BaseActivity
import kotlinx.android.synthetic.main.activity_audio_fdkaac_encode.*
import java.io.FileInputStream
import java.io.FileOutputStream

/**
 * <pre>
 *     author  : devyk on 2020-05-28 21:30
 *     blog    : https://juejin.im/user/578259398ac2470061f3a3fb/posts
 *     github  : https://github.com/yangkun19921001
 *     mailbox : yang1001yk@gmail.com
 *     desc    : This is AudioRecordActivty
 * </pre>
 */

public class FDKAACEncodeActivty : BaseActivity() {



    private lateinit var mFDKAACEncode: FDKAACEncode;

    /**
     * 编码的采样率
     */
    private var mSampleRate = 44100;

    /**
     * 编码的通道
     */
    private var mChannels = 1;

    /**
     * 码率 bitrate/s
     */
    private var mBitRate = 128000;

    override fun initListener() {
        AudioCapture.addRecordListener(object : AudioCapture.OnRecordListener {
            override fun onStart() {
                Handler().post {
                    timeClean()//计时器清零
                    setTimeFormat()
                    timer.start();
                }
                mFDKAACEncode.init(mBitRate, mChannels, mSampleRate)
            }

            override fun onStop() {
                Handler().post {
                    timeClean()//计时器清零
                    timer.stop();
                }
                mFDKAACEncode.destory()
            }

            override fun onData(byteArray: ByteArray) {
                Log.i(TAG, byteArray.size.toString())
                mFDKAACEncode.encode(byteArray, byteArray.size)
            }
        })
    }

    override fun initData() {


    }

    override fun init() {
        //初始化音频采集
        AudioCapture.init()
        mFDKAACEncode = FDKAACEncode();

    }

    override fun getLayoutId(): Int = R.layout.activity_audio_fdkaac_encode


    fun startEncode(view: View) {
        AudioCapture.startRecording()

    }

    private fun setTimeFormat() {
        var hour = ((SystemClock.elapsedRealtime() - timer.getBase()) / 1000 / 60).toInt();
        timer.setFormat("0${hour}:%s");
    }

    fun stopEncode(view: View) {
        AudioCapture.stopRecording()

    }

    private fun timeClean() {
        timer.setBase(SystemClock.elapsedRealtime());
    }
}


