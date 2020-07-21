/***************************************************************************
 *   Copyright (C) 2001 by Matthias Hoelzer-Kluepfel <mhk@caldera.de>      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __USB_DEVICES_H__
#define __USB_DEVICES_H__

#include <QList>
#include <QString>

#include <libusb.h>

class USBDB;

class USBDevice {
public:

	USBDevice(libusb_device *dev, struct libusb_device_descriptor &dev_desc);
	
	~USBDevice();

	int level() const {
		return _level;
	}
	int device() const {
		return _device;
	}
	int parent() const {
		return _parent;
	}
	int bus() const {
		return _bus;
	}
	QString product();

	QString dump();

	static QList<USBDevice*> &devices() {
		return _devices;
	}
	static USBDevice *find(int bus, int device);
	static bool load();
	static void clear();

private:

	static QList<USBDevice*> _devices;
	static libusb_context *_context;

	static USBDB *_db;

	int _bus, _level, _parent, _port, _device, _channels;
	float _speed;

	QString _manufacturer, _product, _serial;

	unsigned int _verMajor, _verMinor, _class, _sub, _prot, _maxPacketSize;

	unsigned int _vendorID, _prodID;

	void collectDataSys(libusb_device *dev);
};

#endif
