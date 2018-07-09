package org.example.toastespexample

import io.reactivex.Single
import okhttp3.ResponseBody
import retrofit2.http.Body
import retrofit2.http.POST

interface EspApi {
    @POST("turnOn")
    fun turnOn(): Single<ResponseBody>

    @POST("turnOff")
    fun turnOff(): Single<ResponseBody>

    @POST("setColor")
    fun setColor(@Body rgb: RGB): Single<ResponseBody>
}