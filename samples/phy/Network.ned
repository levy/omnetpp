//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

module Node
{
    parameters:
        @display("i=device/pc");
    gates:
        input in;
        output out;
    submodules:
        source: Source {
            @display("p=100,100");
        }
        sink: Sink {
            @display("p=300,100");
        }
        phy: <> like IPhy {
            @display("p=200,200");
        }
    connections:
        source.out --> phy.upperLayerIn;
        phy.mediumOut --> out;
        in --> phy.mediumIn;
        phy.upperLayerOut --> sink.in;
}

network Network
{
    submodules:
        client: Node {
            @display("p=100,100");
        }
        server: Node {
            @display("p=200,100");
        }
    connections:
        client.out --> ned.TransmissionChannel { delay = 1ms; } --> server.in;
        server.out --> ned.TransmissionChannel { delay = 1ms; } --> client.in;
}
