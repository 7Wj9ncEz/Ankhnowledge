/*
 * File:   Log.h
 *
 * Creates a logging system for the game
 */

#ifndef LOG_H
#define LOG_H

#include <iostream>

using namespace std;

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

/**
 * Shows the type of log (header or not) and the level of the log type
**/
struct structlog {
    bool headers = false;
    typelog level = WARN;
};

extern structlog LOGCFG;

/**
 * Class that if instantiated creates the Log and shows the log messages in the main.cpp
**/
class LOG {
    public:
        LOG() {}

        /**
         * Shows the Log in the main by it's type/header
         *
         * Parameters:
         * "type" references itself a the type of the log that will be emitted
        **/
        LOG(typelog type) {
            msglevel = type;
            if (LOGCFG.headers) {
                operator << ("["+getLabel(type)+"]");
            }

            else {
                // Nothing to do
            }
        }

        ~LOG() {
            if (opened) {
                cout << endl;
            }

            else {
                // Nothing to do
            }
            opened = false;
        }

        // Creates a template with a generic Type (<class T>)
        template<class T>
        LOG &operator<<(const T &msg) {
            if (msglevel >= LOGCFG.level) {
                cout << msg;
                opened = true;
            }

            else {
                // Nothing to do
            }
            return *this;
        }

    private:
        bool opened = false;
        typelog msglevel = DEBUG;
        inline string getLabel(typelog type) {
            string label = "";

            // Labels the type of log made
            switch (type) {

                case DEBUG:
                    label = "DEBUG"; break;

                case INFO:
                    label = "INFO "; break;

                case WARN:
                    label = "WARN "; break;

                case ERROR:
                    label = "ERROR"; break;

                default:
                    // Nothing to do
                    break;
            }
        return label;
    }
};
