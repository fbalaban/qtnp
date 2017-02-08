// Auto-generated. Do not edit!

// (in-package qtnp.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class Coordinates {
  constructor() {
    this.placemark_type = '';
    this.seed_longitude = 0.0;
    this.seed_latitude = 0.0;
    this.longitude = [];
    this.latitude = [];
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Coordinates
    // Serialize message field [placemark_type]
    bufferInfo = _serializer.string(obj.placemark_type, bufferInfo);
    // Serialize message field [seed_longitude]
    bufferInfo = _serializer.float64(obj.seed_longitude, bufferInfo);
    // Serialize message field [seed_latitude]
    bufferInfo = _serializer.float64(obj.seed_latitude, bufferInfo);
    // Serialize the length for message field [longitude]
    bufferInfo = _serializer.uint32(obj.longitude.length, bufferInfo);
    // Serialize message field [longitude]
    obj.longitude.forEach((val) => {
      bufferInfo = _serializer.float64(val, bufferInfo);
    });
    // Serialize the length for message field [latitude]
    bufferInfo = _serializer.uint32(obj.latitude.length, bufferInfo);
    // Serialize message field [latitude]
    obj.latitude.forEach((val) => {
      bufferInfo = _serializer.float64(val, bufferInfo);
    });
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Coordinates
    let tmp;
    let len;
    let data = new Coordinates();
    // Deserialize message field [placemark_type]
    tmp = _deserializer.string(buffer);
    data.placemark_type = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [seed_longitude]
    tmp = _deserializer.float64(buffer);
    data.seed_longitude = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [seed_latitude]
    tmp = _deserializer.float64(buffer);
    data.seed_latitude = tmp.data;
    buffer = tmp.buffer;
    // Deserialize array length for message field [longitude]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [longitude]
    data.longitude = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.float64(buffer);
      data.longitude[i] = tmp.data;
      buffer = tmp.buffer;
    }
    // Deserialize array length for message field [latitude]
    tmp = _deserializer.uint32(buffer);
    len = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [latitude]
    data.latitude = new Array(len);
    for (let i = 0; i < len; ++i) {
      tmp = _deserializer.float64(buffer);
      data.latitude[i] = tmp.data;
      buffer = tmp.buffer;
    }
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'qtnp/Coordinates';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0c53d7b4e0233648a057076b6c290607';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string placemark_type
    float64 seed_longitude
    float64 seed_latitude
    float64[] longitude
    float64[] latitude
    
    `;
  }

};

module.exports = Coordinates;
