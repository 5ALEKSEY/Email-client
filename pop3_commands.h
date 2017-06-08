#ifndef POP3_COMMANDS_H
#define POP3_COMMANDS_H

enum pop3_Commands
{
    USER_PASS = 0,
    STAT,
    RETR,
    LIST,
    DELE,
    QUIT
};
 Q_DECLARE_METATYPE(pop3_Commands);

#endif // POP3_COMMANDS_H
