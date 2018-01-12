//
//  voiceMail.cpp
//  VoiceMail
//
//  Created by Jeffrey Ding on 1/8/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

// VoiceMail implementation

#include "VoiceMail.h"
#include <string>
#include <iostream>
using namespace std;

void VoiceMail::record(string msg)
{
    m_message = msg;
}

void VoiceMail::erase()
{
    m_message = "";
}

void VoiceMail::playback() const
{
    if (m_message.empty())
        cout << "There is no message to play back." << endl;
    else
        cout << m_message << endl;
}
