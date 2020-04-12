/* MIT License
 *
 * Copyright (c) 2020 SODIUM-24, LLC
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
 *
 */

#include <ignition/msgs.hh>
#include <ignition/transport.hh>
#include <ignition/transport/Discovery.hh>
#include <memory>
#include <string>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <thread>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <option>\n\n";
        std::cout << "Option: list";
        return 1;
    }

    if (std::string(argv[1]) == "list")
    {

        std::unique_ptr<ignition::transport::MsgDiscovery> discovery = 
        std::unique_ptr<ignition::transport::MsgDiscovery>(
            new ignition::transport::MsgDiscovery(ignition::transport::Uuid().ToString(), ignition::transport::NodeShared::kMsgDiscPort));

        discovery->Start();

        while (true)
        {
            std::vector<std::string> topics;
            discovery->TopicList(topics);

            std::cout << "Topic List:\n";

            for (const std::string& topic : topics)
            {
                std::cout << "- " << topic << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }
    else
    {
        std::cout << "Unknown option!\n";
        return 1;
    }

    return 0;
}

