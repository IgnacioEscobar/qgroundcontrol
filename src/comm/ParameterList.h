/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H

#include <QMap>

#include "mavlink_types.h"
#include "QGCParamID.h"
#include "Parameter.h"
#include "QVector"
#include "OpalRT.h"

// Forward declare ParameterList before including OpalLink.h because a member of type ParameterList is used in OpalLink
namespace OpalRT
{
        class ParameterList;
}
#include "OpalLink.h"
namespace OpalRT
{
    class ParameterList
    {
    public:

        class const_iterator
        {
            friend class ParameterList;

        public:
            inline const_iterator() {}
            const_iterator(const const_iterator& other);

            const_iterator& operator+=(int i) {index += i; return *this;}
            bool operator<(const const_iterator& other) {return (this->paramList == other.paramList)
                                                         &&(this->index<other.index);}
            bool operator==(const const_iterator& other) {return (this->paramList == other.paramList)
                                                          &&(this->index==other.index);}
            bool operator!=(const const_iterator& other) {return !((*this) == other);}
            const Parameter& operator*() const {return paramList[index];}
            const Parameter* operator->() const {return &paramList[index];}

            const_iterator& operator++() {++index; return *this;}
        private:
            const_iterator(QList<Parameter>);
            QList<Parameter> paramList;
            int index;
        };


        ParameterList();
        ~ParameterList();
        int setValue(int compid, QGCParamID paramid, float value);
        float getValue(int compid, QGCParamID paramid);
        int count();
        int indexOf(const Parameter& p) {return paramVector->indexOf(p);}

        const_iterator begin() const;
        const_iterator end() const;

    protected:
        QMap<int, QMap<QGCParamID, Parameter> > *params;
        QVector<Parameter> *paramVector;
        void getParameterList(QMap<QString, unsigned short>*);



    };
}
#endif // PARAMETERLIST_H
