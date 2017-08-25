//<editor-fold desc="Preamble">
/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (C) 8/17/17 Carlos Brito
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */
//</editor-fold>

//<editor-fold desc="Description">
/**
 * @file PointData.hpp
 * @author Carlos Brito (carlos.brito524@gmail.com)
 * @date 8/17/17.
 * 
 * @brief Contains class definitions for DataPoint.
 *
 */
//</editor-fold>
#ifndef SERVER_DATAPOINT_HPP
#define SERVER_DATAPOINT_HPP

#include <string>
#include <boost/property_tree/ptree.hpp>

namespace sunspec {
    namespace data {

        /**
         * @class DataPoint
         * @author Carlos Brito (carlos.brito524@gmail.com)
         * @date 8/17/17.
         *
         * @brief A record of some measurement.
         *
         * # Description
         * A `DataPoint` is a record of data that contains information
         * about some measurement (or sample). The measurement is
         * identified with and id and it takes any type of value. We
         * store all fields of data, like the `id` and `description`
         * as `std::strings`. This is because we are only interested in
         * getting the data instead of parsing it. To know what the types
         * of data are then we would have to look at the SDMX spec and assign
         * the types accordingly.
         */
        struct PointData {
            std::string id;        /// Name of the data point record (to know what it represents).
            std::string sf = "0";  /// The scale factor. I.e. $ 10^(sf) $. Defaults to 0.
            std::string d;         /// User friendly description of the data point.
            std::string u;         /// Unit of measure of the value.
            std::string x;         /// Index of record. If we have multiple records of same type we need to differentiate them.
            std::string t;         /// Time at which the point was obtained in RFC3339 format.
            std::string value;     /// Value of the data point.

            /**
             * Empty constructor.
             */
            PointData() = default;

            /**
             * Constructs a DataPoint object.
             * @param id Name of the data point.
             * @param value Value of data point of type `T`.
             */
            PointData(std::string id, std::string value) : id(id), value(value) {}

            /**
             * Copy constructor.
             */
            PointData(const PointData &) = default;

            /**
             * Builds a PointData out of a SDX specification. This specification
             * can be found in the SunSpec Data Model Exchange Specification and
             * its syntax is XML.
             * @param point_element The `ptree` object (in XML) element of the point record.
             * @return Returns a `PointData` object with the same data as the element.
             * @throws XMLError Throws if there was an error parsing the XML. This will mean
             * that the data contained in the `point_element` is empty or is malformed.
             */
            static PointData from_xml(const boost::property_tree::ptree &point_element);

            /**
             * Builds a PointData out of a SDX specification. This specification
             * can be found in the SunSpec Data Model Exchange Specification and
             * its syntax is XML.
             * @param point_record A `std::string` containing the XML representation
             * of the point record.
             * @return Returns a `PointData` object with the same data as the XML
             * representation that was passed.
             * @throws XMLError Throws if there was an error parsing the XML. This will mean
             * that the data contained in the `point_record` is empty or is malformed.
             */
            static PointData from_xml(const std::string &point_record);
        };
    }
}

#endif //SERVER_DATAPOINT_HPP