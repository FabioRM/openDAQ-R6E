//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (PythonGenerator).
// </auto-generated>
//------------------------------------------------------------------------------

/*
 * Copyright 2022-2023 Blueberry d.o.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "py_opendaq/py_opendaq.h"
#include "py_core_types/py_converter.h"

PyDaqIntf<daq::IDataPacket, daq::IPacket> declareIDataPacket(pybind11::module_ m)
{
    return wrapInterface<daq::IDataPacket, daq::IPacket>(m, "IDataPacket");
}

void defineIDataPacket(pybind11::module_ m, PyDaqIntf<daq::IDataPacket, daq::IPacket> cls)
{
    cls.doc() = "Packet that contains data sent by a signal. The data can be either explicit, or implicit.";

    m.def("DataPacket", &daq::DataPacket_Create);
    m.def("DataPacketWithDomain", &daq::DataPacketWithDomain_Create);

    cls.def_property_readonly("data_descriptor",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getDataDescriptor().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets the signal descriptor of the signal that sent the packet at the time of sending.");
    cls.def_property_readonly("sample_count",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getSampleCount();
        },
        "Gets the number of samples in the packet.");
    cls.def_property_readonly("offset",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getOffset().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets current packet offset. This offset is later applied to the data rule used by a signal to calculate actual data value. This value is usually a time or other domain value. Packet offset is particularly useful when one wants to transfer a gap in otherwise equidistant samples. If we have a linear data rule, defined by equation f(x) = k*x + n, then the data value will be calculated by the equation g(x) = offset + f(x).");
    /*
    cls.def_property_readonly("data",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getData();
        },
        py::return_value_policy::take_ownership,
        "Gets the calculated/scaled data address of the packet.");
    */
    /*
    cls.def_property_readonly("raw_data",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getRawData();
        },
        py::return_value_policy::take_ownership,
        "Gets a pointer to the raw packet data. `nullptr` if the signal's data rule is implicit.");
    */
    cls.def_property_readonly("data_size",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getDataSize();
        },
        "Gets size of data buffer in bytes.");
    cls.def_property_readonly("raw_data_size",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getRawDataSize();
        },
        "Gets size of raw data buffer in bytes.");
    cls.def_property_readonly("domain_packet",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getDomainPacket().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets the associated domain Data packet.");
    cls.def_property_readonly("packet_id",
        [](daq::IDataPacket *object)
        {
            const auto objectPtr = daq::DataPacketPtr::Borrow(object);
            return objectPtr.getPacketId();
        },
        "Gets the unique packet id.");
}
