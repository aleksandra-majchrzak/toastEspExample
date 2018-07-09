package org.example.toastespexample

import android.graphics.Color
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.util.Log
import io.reactivex.disposables.CompositeDisposable
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity(), OnLedChangedListener {

    private var isOn = false;
    private var allDisposables: CompositeDisposable = CompositeDisposable()


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        onOffButton.setOnClickListener({ v ->
            if (isOn) {
                allDisposables.add(EspService.turnOff(this))
            } else {
                allDisposables.add(EspService.turnOn(this))
            }
        })

        colorPickerView.addOnColorSelectedListener { color ->
            if (isOn) {
                val red = Color.red(color)
                val green = Color.green(color)
                val blue = Color.blue(color)
                allDisposables.add(EspService.setColor(red, green, blue, this))
            } else {
                colorPickerView.setColor(-1, false)
            }
        }
    }

    override fun onStop() {
        super.onStop()
        allDisposables.clear()
    }

    override fun onLedOnSuccess() {
        isOn = true
        onOffButton.text = getString(R.string.turn_off)
    }

    override fun onLedOnError() {
        Log.d(MainActivity::class.java.simpleName, "onLedOnError")
    }

    override fun onLedOffSuccess() {
        isOn = false
        onOffButton.text = getString(R.string.turn_on)
        colorPickerView.setColor(-1, false)
    }

    override fun onLedOffError() {
        Log.d(MainActivity::class.java.simpleName, "onLedOffError")
    }

    override fun onSetColorSuccess() {
        Log.d(MainActivity::class.java.simpleName, "onSetColorSuccess")
    }

    override fun onSetColorError() {
        Log.d(MainActivity::class.java.simpleName, "onSetColorError")
    }
}
