![Java Logo](img/java-logo.png) <img src="img/Android_Robot.png" width="100">
# ARISEN SDK for Java: Android ABIRSN Serialization Provider ![ARISEN Alpha](https://img.shields.io/badge/ARISEN-Alpha-blue.svg)

[![Software License](https://img.shields.io/badge/license-MIT-lightgrey.svg)](./LICENSE)
![Language Java](https://img.shields.io/badge/Language-C%2B%2B%2FJava-yellow.svg)
![](https://img.shields.io/badge/Deployment%20Target-Android%206%2B-blue.svg)

Android ABIRSN Serialization Provider is a pluggable serialization provider for ARISEN SDK for Java.

Serialization providers are responsible for ABI-driven transaction and action serialization and deserialization between JSON and binary data representations. This particular serialization provider wraps ABIRSN, a C/C++ library that facilitates this conversion.

*All product and company names are trademarks™ or registered® trademarks of their respective holders. Use of them does not imply any affiliation with or endorsement by them.*

*The Android robot is reproduced or modified from work created and shared by Google and used according to terms described in the Creative Commons 3.0 Attribution License.*

## Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Direct Usage](#direct-usage)
- [Android Example App](#android-example-app)
- [Releases](#releases)
- [Want to Help?](#want-to-help)
- [License & Legal](#license)

## Prerequisites

* Android Studio 3.3.2 or higher
* NDK 18+ (C++ 17 standard support required)
* Cmake 3.6.0+
* Gradle 4.10.1+
* Gradle Plugin 3.3.0+
* For Android, Android 6 (Marshmallow)+

This project relies on platform functionality and libraries only present in Android 6+ and the Android NDK. Therefore, any project depending on ABIRSN Serialization Provider with [ARISEN SDK for Java](https://github.com/ARISEN/arisen-java) **must be an Android 6+ project**. Other serialization providers, however, can be created to support earlier Android versions or other platforms. If your project requires earlier Android version or alternate platform support, or if you'd like to create a serialization provider and have questions, please reach out to us by [logging an issue](/../../issues/new).

## Installation

ABIRSN  Serialization Provider is intended to be used in conjunction with [ARISEN SDK for Java](https://github.com/ARISEN/arisen-java) as a provider plugin.

To use ABIRSN Serialization Provider with ARISEN SDK for Java in your app, add the following modules to your `build.gradle`:

```groovy
implementation 'labs.peeps:arisenjava:0.1.2'
implementation 'labs.peeps:arisenjavaandroidABIRSNserializationprovider:0.1.1'
```

You must also add the following to the `android` section of your application's `build.gradle`:

```groovy
// Needed to get bitcoin-j to produce a valid apk for android.
packagingOptions {
    exclude 'lib/x86_64/darwin/libscrypt.dylib'
    exclude 'lib/x86_64/freebsd/libscrypt.so'
    exclude 'lib/x86_64/linux/libscrypt.so'
}
```

The `build.gradle` files for the project currently include configurations for publishing the project to Artifactory.  These should be removed if you are not planning to use Artifactory or you will encounter build errors.  To do so, make the changes marked by comments throughout the files.

Then refresh your gradle project.

Now ABIRSN Serialization Provider is ready for use within ARISEN SDK for Java according to the [ARISEN SDK for Java Basic Usage instructions](https://github.com/ARISEN/arisen-java/tree/master#basic-usage).

## Direct Usage

If you wish to use ABIRSN Serialization Provider directly, its public methods can be called like this:

```java
try {
    ABIRSN ABIRSN = new ABIRSNSerializationProviderImpl()
} catch (SerializationProviderError serializationProviderError) {
    serializationProviderError.printStackTrace();
}

String hex = "1686755CA99DE8E73E1200" // some binary data
String json = "{"name": "John"}" // some JSON

try {
    String jsonToBinaryTransaction = ABIRSN.serializeTransaction(json)
} catch (SerializeTransactionError err) {
    err.printStackTrace();
}

try {
    String binaryToJsonTransaction = ABIRSN.deserializeTransaction(hex)
} catch (DeserializeTransactionError err) {
    err.printStackTrace();
}
```

## Android Example App

If you'd like to see ARISEN SDK for Java: Android ABIRSN Serialization Provider in action, check out our open source [Android Example App](https://github.com/ARISENIO/arisen-java-android-example-app)--a working application that fetches an account's token balance and pushes a transfer action.

## Releases

2/27/20

Version 0.1.1 The version consumes the new arisen-java library version 0.1.2.

## Want to help?

Interested in contributing? That's awesome! Here are some [Contribution Guidelines](./CONTRIBUTING.md) and the [Code of Conduct](./CONTRIBUTING.md#conduct).

We're always looking for ways to improve this library. Check out our [#enhancement Issues](/../../issues?q=is%3Aissue+is%3Aopen+label%3Aenhancement) for ways you can pitch in.

## License

[MIT](./LICENSE)
