/*
 *  Copyright (C) 2010 Tuomo Penttinen, all rights reserved.
 *
 *  Author: Tuomo Penttinen <tp@herqq.org>
 *
 *  This file is part of Herqq UPnP (HUPnP) library.
 *
 *  Herqq UPnP is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Herqq UPnP is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Herqq UPnP. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HACTIONINFO_H_
#define HACTIONINFO_H_

#include "../general/hupnp_fwd.h"
#include "../general/hupnp_global.h"

class QString;

namespace Herqq
{

namespace Upnp
{

class HActionInfoPrivate;

/*!
 * \brief This class is used to contain information of a UPnP action
 * found in a UPnP service description document.
 *
 * UPnP service description documents specify the actions and state variables
 * of the service. An instance of this class contain the information of an
 * action found in a service description document:
 *
 * - name() returns the name of the action.
 * - inputArguments() return the arguments that has to be provided to the
 * action when it is invoked.
 * - outputArguments() return the arguments the action will provide after a
 * successful action invocation.
 * - returnArgumentName() identifies the output argument that has been
 * designated as the return value. Note that this may not be defined.
 *
 * In addition to the information found in the service description document,
 * the HService containing the HAction that is depicted by the HActionInfo object
 * may have specified additional information about the action. Currently
 * only inclusionRequirement() is available and it details
 * whether the action is considered as mandatory or optional.
 *
 * \headerfile hactioninfo.h HActionInfo
 *
 * \ingroup dataelements
 *
 * \remarks this class is not thread-safe.
 *
  \sa HAction, HDeviceInfo, HServiceInfo and HStateVariableInfo.
 */
class H_UPNP_CORE_EXPORT HActionInfo
{
friend H_UPNP_CORE_EXPORT bool operator==(
    const HActionInfo&, const HActionInfo&);

private:

    HActionInfoPrivate* h_ptr;

public:

    /*!
     * Creates a new, invalid instance.
     *
     * \sa isValid()
     */
    HActionInfo();

    /*!
     * Creates a new instance.
     *
     * \param name specifies the name of the action.
     *
     * \param incReq specifies whether the action is required by the containing
     * service.
     *
     * \param err specifies a pointer to a \c QString, which contains an
     * error description in case the construction failed. This
     * parameter is optional.
     *
     * \sa isValid()
     */
    HActionInfo(
        const QString& name,
        HInclusionRequirement incReq = InclusionMandatory,
        QString* err = 0);

    /*!
     * Creates a new instance.
     *
     * \param name specifies the name of the action.
     *
     * \param inputArguments specifies the input arguments of the action. These
     * are the arguments the user has to provide when the action is invoked.
     *
     * \param outputArguments specifies the output arguments of the action.
     * These are the arguments the action will "return" when the action invocation
     * is successfully completed.
     *
     * \param hasRetVal specifies whether the action has a return value. If this
     * is \e true the first element of the \c outputArguments is considered as
     * the return value. Note also that if this is true the \c outputArguments
     * cannot be empty.
     *
     * \param incReq specifies whether the action is required or optional.
     *
     * \param err specifies a pointer to a \c QString, which contains an
     * error description in case the construction failed. This
     * parameter is optional.
     *
     * \sa isValid()
     */
    HActionInfo(
        const QString& name,
        const HActionArguments& inputArguments,
        const HActionArguments& outputArguments,
        bool hasRetVal,
        HInclusionRequirement incReq = InclusionMandatory,
        QString* err = 0);

    /*!
     * Copies the contents of the other to this.
     *
     * \param other specifies the object to be copied.
     */
    HActionInfo(const HActionInfo& other);

    /*!
     * Destroys the instance.
     *
     * Destroys the instance.
     */
    ~HActionInfo();

    /*!
     * Assigns the contents of the other to this.
     *
     * \param other specifies the object to be copied.
     */
    HActionInfo& operator=(const HActionInfo& other);

    /*!
     * Returns the name of the action.
     *
     * This is the name specified in the corresponding service description file.
     *
     * \return the name of the action.
     */
    QString name() const;

    /*!
     * Returns the input arguments the action expects.
     *
     * These are the arguments the user has to provide when invoking the
     * action that this info object portrays.
     *
     * \return the input arguments the action.
     *
     * \sa outputArguments()
     */
    const HActionArguments& inputArguments() const;

    /*!
     * Returns the output arguments of the action.
     *
     * These are the arguments each successful action invocation will "return"
     * to user as output values.
     *
     * \return the output arguments of the action.
     *
     * \sa inputArguments()
     */
    const HActionArguments& outputArguments() const;

    /*!
     * Returns the name of the output argument that is marked as the
     * action's return value.
     *
     * \return the name of the output argument that is marked as the action's
     * return value, or an empty string, if no output argument has been marked as
     * the action's return value.
     */
    QString returnArgumentName() const;

    /*!
     * Indicates whether the action is required or optional.
     *
     * \return value indicating whether the action is required or optional.
     */
    HInclusionRequirement inclusionRequirement() const;

    /*!
     * Indicates if the object is empty.
     *
     * \return \e true in case the object is valid.
     */
    bool isValid() const;
};

/*!
 * Compares the two objects for equality.
 *
 * \return \e true in case the object are logically equivalent.
 *
 * \relates HActionInfo
 */
H_UPNP_CORE_EXPORT bool operator==(const HActionInfo&, const HActionInfo&);

/*!
 * Compares the two objects for inequality.
 *
 * \return \e true in case the object are not logically equivalent.
 *
 * \relates HActionInfo
 */
H_UPNP_CORE_EXPORT bool operator!=(const HActionInfo&, const HActionInfo&);

/*!
 * Returns a value that can be used as a unique key in a hash-map identifying
 * the object.
 *
 * \param key specifies the HActionInfo object from which the hash value is created.
 *
 * \return a value that can be used as a unique key in a hash-map identifying
 * the object.
 *
 * \remarks the hash is calculated from the name() of the HActionInfo.
 *
 * \relates HActionInfo
 */
H_UPNP_CORE_EXPORT quint32 qHash(const HActionInfo& key);

}
}

#endif /* HACTIONINFO_H_ */
