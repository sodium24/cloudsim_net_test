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

#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <thread>
#include "advertisetopics.h"

AdvertiseTopics::AdvertiseTopics()
{
}

AdvertiseTopics::~AdvertiseTopics()
{
}

void AdvertiseTopics::Advertise(int num_nodes, int topics_per_node)
{
    m_nodes.resize(num_nodes);

    for (int n=0; n<num_nodes; n++)
    {
        m_nodes[n] = std::make_unique<ignition::transport::Node>();

        for (int t=0; t<topics_per_node; t++)
        {

            std::string topic_name = "/";
            for (int c=0; c<16; c++)
            {
                topic_name.push_back((char)(rand()%26) + 'a');
            }

            auto pub = m_nodes[n]->Advertise<ignition::msgs::StringMsg>(topic_name);
            m_publishers.push_back(pub);
        }
    }
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <num_nodes> <topics_per_node>\n";
        return 1;
    }

    int num_nodes = atoi(argv[1]);
    int topics_per_node = atoi(argv[2]);

    AdvertiseTopics advertise;
    advertise.Advertise(num_nodes, topics_per_node);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}

