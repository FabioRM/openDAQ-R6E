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

PyDaqIntf<daq::IDataRule, daq::IBaseObject> declareIDataRule(pybind11::module_ m)
{
    py::enum_<daq::DataRuleType>(m, "DataRuleType")
        .value("Other", daq::DataRuleType::Other)
        .value("Linear", daq::DataRuleType::Linear)
        .value("Constant", daq::DataRuleType::Constant)
        .value("Explicit", daq::DataRuleType::Explicit);

    return wrapInterface<daq::IDataRule, daq::IBaseObject>(m, "IDataRule");
}

void defineIDataRule(pybind11::module_ m, PyDaqIntf<daq::IDataRule, daq::IBaseObject> cls)
{
    cls.doc() = "Rule that defines how a signal value is calculated from an implicit initialization value when the rule type is not `Explicit`.";

    m.def("LinearDataRule", &daq::LinearDataRule_Create);
    m.def("ConstantDataRule", &daq::ConstantDataRule_Create);
    m.def("ExplicitDataRule", &daq::ExplicitDataRule_Create);
    m.def("ExplicitDomainDataRule", &daq::ExplicitDomainDataRule_Create);
    m.def("DataRule", &daq::DataRule_Create);
    m.def("DataRuleFromBuilder", &daq::DataRuleFromBuilder_Create);

    cls.def_property_readonly("type",
        [](daq::IDataRule *object)
        {
            const auto objectPtr = daq::DataRulePtr::Borrow(object);
            return objectPtr.getType();
        },
        "Gets the type of the data rule.");
    cls.def_property_readonly("parameters",
        [](daq::IDataRule *object)
        {
            const auto objectPtr = daq::DataRulePtr::Borrow(object);
            return objectPtr.getParameters().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets a dictionary of string-object key-value pairs representing the parameters used to evaluate the rule.");
}
