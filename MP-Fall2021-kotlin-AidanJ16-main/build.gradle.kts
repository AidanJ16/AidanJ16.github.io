@file:Suppress("SpellCheckingInspection")

/*
 * This file configures the build system that creates your Android app.
 * The syntax is Kotlin, but many of the idioms are likely unfamiliar.
 * You do not need to understand the contents of this file, nor should you modify it.
 * Any changes will be overwritten during official grading.
 */

buildscript {
    repositories {
        google()
    }
    dependencies {
        classpath("com.android.tools.build:gradle:7.0.3")
        classpath("org.jetbrains.kotlin:kotlin-gradle-plugin:1.5.31")
    }
}
plugins {
    id("org.jlleitschuh.gradle.ktlint") version "10.2.0"
}
allprojects {
    repositories {
        google()
        mavenCentral()
        maven("https://jitpack.io")
    }
}
tasks.register<Delete>("clean") {
    delete = setOf(rootProject.buildDir)
}
