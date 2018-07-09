package org.example.toastespexample

import io.reactivex.android.schedulers.AndroidSchedulers
import io.reactivex.disposables.Disposable
import io.reactivex.schedulers.Schedulers
import okhttp3.OkHttpClient
import okhttp3.logging.HttpLoggingInterceptor
import retrofit2.Retrofit
import retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory
import retrofit2.converter.gson.GsonConverterFactory

object EspService {

    private val api by lazy {
        val interceptor = HttpLoggingInterceptor()
        interceptor.level = HttpLoggingInterceptor.Level.BODY
        val client = OkHttpClient.Builder().addInterceptor(interceptor).build()

        val retrofit = Retrofit.Builder()
                .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
                .addConverterFactory(GsonConverterFactory.create())
                .baseUrl("http://___.___.___.___/") //your module ip
                .client(client)
                .build()

        return@lazy retrofit.create(EspApi::class.java)
    }

    fun turnOn(listener: OnLedChangedListener): Disposable {
        return api.turnOn().subscribeOn(Schedulers.io()).observeOn(AndroidSchedulers.mainThread()).subscribe(
                { listener.onLedOnSuccess() },
                { error -> listener.onLedOnError() })
    }

    fun turnOff(listener: OnLedChangedListener): Disposable {
        return api.turnOff().subscribeOn(Schedulers.io()).observeOn(AndroidSchedulers.mainThread()).subscribe(
                { listener.onLedOffSuccess() },
                { error -> listener.onLedOffError() })
    }

    fun setColor(red: Int, green: Int, blue: Int, listener: OnLedChangedListener): Disposable {
        return api.setColor(RGB(red, green, blue)).subscribeOn(Schedulers.io()).observeOn(AndroidSchedulers.mainThread()).subscribe(
                { listener.onSetColorSuccess() },
                { error -> listener.onSetColorError() })
    }
}