/*
 * MIT License
 *
 * Copyright (c) 2020 - Now chenxiaohui <371986482@qq.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <fstream>
#include <iostream>
#include <utils/CEnvironment.hpp>

namespace stk
{

CEnvironment::CEnvironment()
{
    /* do nothing */
}

CEnvironment* CEnvironment::GetInstance()
{
    static CEnvironment* instance = new CEnvironment();

    return instance;
}

bool CEnvironment::Init(std::string const & _config_file)
{
    if (_config_file.empty())
    {
        /* config file is empty */
        return false;
    }

    std::ifstream configFile { _config_file.c_str() };

    if (!configFile)
    {
        /* can't create input file stream */
        return false;
    }

    std::string line, tag, key, val;

    std::map<std::string, std::string> kv;
    std::map<std::string, std::map<std::string, std::string> >::iterator it;

    m_tkv.clear();

    while ( getline(configFile, line) )
    {
        if (readLine(line, tag, key, val))
        {
            it = m_tkv.find(tag);

            if (it != m_tkv.end())
            {
                /* append key-value */
                it->second[key] = val;
            }
            else
            {
                /* only append tag to map */
                kv.clear();
                m_tkv.insert(std::make_pair(tag, kv));
            }
        }

        key.clear();
        val.clear();
    }

    /* close config file */
    configFile.close();

    m_inited = true;

    return true;
}

std::string CEnvironment::Get(std::string const & _key)
{
    if (!m_inited)
    {
        return std::string("");
    }

    std::string rst { "" };

    for (auto &it : m_tkv)
    {
        auto kvIt = it.second;

        auto item = kvIt.find(_key);

        if (item == kvIt.end())
        {
            continue;
        }
        else
        {
            rst = item->second;
            break;
        }
    }

    return rst;
}

void CEnvironment::Set(std::string const & _key, std::string const & _val)
{
    if ( !m_inited || _key.empty() )
    {
        return;
    }

    static const std::string USER_TAG { "user" };

    auto it = m_tkv.find(USER_TAG);

    if ( it != m_tkv.end() )
    {
        auto item = it->second.find(_key);

        if ( item != it->second.end() )
        {
            /* replace value */
            item->second = _val;
        }
        else
        {
            it->second.insert(std::make_pair(_key, _val));
        }
    }
    else
    {
        std::map<std::string, std::string> kv;
        kv[_key] = _val;

        m_tkv.insert(std::make_pair(USER_TAG, kv));
    }
}

bool CEnvironment::isSpace(char _c)
{
    if ( (' ' == _c) || ('\t' == _c) )
    {
        return true;
    }

    return false;
}

bool CEnvironment::isComment(char _c)
{
    if ('#' == _c)
    {
        return true;
    }

    return false;
}

void CEnvironment::trim(std::string & _str)
{
    if ( _str.empty() )
    {
        return;
    }

    int idx = 0;

    /* remove all the space */
    while ( (idx = _str.find(' ', idx)) != std::string::npos )
    {
        _str.erase(idx, 1);
    }
}

bool CEnvironment::readLine(std::string const & _line, std::string & _tag, std::string & _key, std::string & _val)
{
    if ( _line.empty() )
    {
        return false;
    }

    std::string line = _line;

    trim(line);

    int pos { 0 };

    int posStart { 0 };
    unsigned long int posEnd   { line.size() - 1U };

    if ( (pos = line.find('#')) != -1)
    {
        if (0 == pos)
        {
            return false;
        }

        posEnd = pos - 1;
    }

    /* tag */

    int posTagStart { 0 };
    int posTagEnd   { 0 };

    if ( ((posTagStart = line.find('[')) != -1) && ((posTagEnd = line.find(']')) != -1) )
    {
        if ( (posTagStart < posTagEnd) )
        {
            if ( (posTagStart + 1) < (posTagEnd - 1) )
            {
                _tag = line.substr(posTagStart + 1, posTagEnd - 1);
                return true;
            }
            else
            {
                /* tag is empty */
                return false;
            }
        }
    }

    std::string subLine = line.substr(posStart, posEnd - posStart + 1);

    /* key-value */

    if ( (pos = subLine.find('=')) == -1 )
    {
        /* not tag and KV not contian delimiter */
        return false;
    }

    _key = subLine.substr(0, pos);
    _val = subLine.substr(pos + 1, posEnd - pos);

    if ((pos = _val.find("\r")) > 0)
    {
        _val.replace(pos, 1, "");
    }

    if ((pos = _val.find("\n")) > 0)
    {
        _val.replace(pos, 1, "");
    }

    //std::cout << " ==> key = " << _key << " val = " << _val << std::endl;

    return true;
}

}