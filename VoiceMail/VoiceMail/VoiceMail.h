//
//  voiceMail.hpp
//  VoiceMail
//
//  Created by Jeffrey Ding on 1/8/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

// VoiceMail interface

#include <string>

class VoiceMail
{
    public:
        void record(std::string msg);
        void erase();
        void playback() const;
    private:
        std::string m_message;
};
