#include "error.h"
Error::Error() : Error(-1,"unknown error") { }

Error::Error(int id, std::string text) : error_id( id ), error_text( text ) { }

Error::Error(const Error& other)
{
    error_id = other.error_id;
    error_text = other.error_text;
}

Error& Error::operator=(const Error& other)
{
    error_id = other.error_id;
    error_text = other.error_text;
    return *this;
}

void Error::setId(int id)
{
    error_id = id;
}

void Error::setText(std::string text)
{
    error_text = text;
}

int Error::getId() const
{
    return error_id;
}

std::string Error::getText() const
{
    return error_text;
}

/**<  */
