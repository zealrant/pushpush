pushpush
========

How to build it
-----

### env variables

세개의 환경 변수에 맞춰서 linux 와 android 의 빌드 설정을 했다.
> SDK_ROOT=

> NDK_ROOT=

> COCOS2DX_ROOT=

### Android
`proj.android/local.properties` 파일의 `android.library.reference.1` 값을 `${cocos2d_root}/cocos2dx/platform/android/java` 으로 상대 경로로 설정한다. 반드시 상대 경로여야만 한다.

`local.properties` 에 `sdk.dir` 과 `ndk.dir` 을 본인 환경에 맞게 설정한다.

`build_native.sh` 를 실행해서 `libs/armeabi/libcocos2dcpp.so` 을 생성하고

`ant release/debug` 로 apk 를 생성한다.


### Linux
`COCOS2DX_ROOT=` 을 설정하고 `./build.sh` 만 실행한다.
