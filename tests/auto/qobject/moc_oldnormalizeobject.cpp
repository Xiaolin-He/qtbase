/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

/****************************************************************************
** Meta object code from reading C++ file 'oldnormalizeobject.h'
**
** Created: Wed Nov 18 11:43:05 2009
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
*****************************************************************************/

// Yhis file was generated from moc version 4.6 to test binary compatibility
// It should *not* be generated by the current moc

#include "oldnormalizeobject.h"

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_OldNormalizeObject[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   20,   19,   19, 0x05,
      57,   20,   19,   19, 0x05,
     100,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     149,   20,   19,   19, 0x0a,
     180,   20,   19,   19, 0x0a,
     221,   20,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_OldNormalizeObject[] = {
    "OldNormalizeObject\0\0ref\0"
    "typeRefSignal(Template<Class&>&)\0"
    "constTypeRefSignal(Template<const Class&>)\0"
    "typeConstRefSignal(Template<const Class&>const&)\0"
    "typeRefSlot(Template<Class&>&)\0"
    "constTypeRefSlot(Template<const Class&>)\0"
    "typeConstRefSlot(Template<const Class&>const&)\0"
};

const QMetaObject OldNormalizeObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_OldNormalizeObject,
      qt_meta_data_OldNormalizeObject, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &OldNormalizeObject::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *OldNormalizeObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *OldNormalizeObject::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_OldNormalizeObject))
        return static_cast<void*>(const_cast< OldNormalizeObject*>(this));
    return QObject::qt_metacast(_clname);
}

int OldNormalizeObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: typeRefSignal((*reinterpret_cast< Template<Class&>(*)>(_a[1]))); break;
        case 1: constTypeRefSignal((*reinterpret_cast< const Template<const Class&>(*)>(_a[1]))); break;
        case 2: typeConstRefSignal((*reinterpret_cast< Template<const Class&>const(*)>(_a[1]))); break;
        case 3: typeRefSlot((*reinterpret_cast< Template<Class&>(*)>(_a[1]))); break;
        case 4: constTypeRefSlot((*reinterpret_cast< const Template<const Class&>(*)>(_a[1]))); break;
        case 5: typeConstRefSlot((*reinterpret_cast< Template<const Class&>const(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void OldNormalizeObject::typeRefSignal(Template<Class&> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void OldNormalizeObject::constTypeRefSignal(const Template<const Class&> & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void OldNormalizeObject::typeConstRefSignal(Template<Class const&> const & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
