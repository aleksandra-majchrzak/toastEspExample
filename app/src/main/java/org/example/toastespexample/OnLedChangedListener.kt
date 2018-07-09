package org.example.toastespexample

interface OnLedChangedListener {
    fun onLedOnSuccess()
    fun onLedOnError()
    fun onLedOffSuccess()
    fun onLedOffError()
    fun onSetColorSuccess()
    fun onSetColorError()
}