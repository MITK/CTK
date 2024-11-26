/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Davide Punzo, punzodavide@hotmail.it,
  and development was supported by the Center for Intelligent Image-guided Interventions (CI3).

=========================================================================*/

#ifndef __ctkDICOMQueryJob_h
#define __ctkDICOMQueryJob_h

// Qt includes
#include <QMap>
#include <QObject>
#include <QSharedPointer>
#include <QVariant>

// ctkCore includes
class ctkAbstractWorker;

// ctkDICOMCore includes
#include "ctkDICOMCoreExport.h"
#include "ctkDICOMJob.h"
class ctkDICOMQueryJobPrivate;
class ctkDICOMServer;

/// \ingroup DICOM_Core
class CTK_DICOM_CORE_EXPORT ctkDICOMQueryJob : public ctkDICOMJob
{
  Q_OBJECT
  Q_PROPERTY(int maximumPatientsQuery READ maximumPatientsQuery WRITE setMaximumPatientsQuery);

public:
  typedef ctkDICOMJob Superclass;
  explicit ctkDICOMQueryJob();
  virtual ~ctkDICOMQueryJob();

  ///@{
  /// Filters are keyword/value pairs as generated by
  /// the ctkDICOMWidgets in a human readable (and editable)
  /// format.  The Query is responsible for converting these
  /// into the appropriate dicom syntax for the C-Find
  /// Currently supports the keys: Name, Study, Series, ID, Modalities,
  /// StartDate and EndDate
  /// Key         DICOM Tag                Type        Example
  /// -----------------------------------------------------------
  /// Name        DCM_PatientName          QString     JOHNDOE
  /// Study       DCM_StudyDescription     QString
  /// Series      DCM_SeriesDescription    QString
  /// ID          DCM_PatientID            QString
  /// Modalities  DCM_ModalitiesInStudy    QStringList CT, MR, MN
  /// StartDate   DCM_StudyDate            QString     20090101
  /// EndDate     DCM_StudyDate            QString     20091231
  /// No filter (empty) by default.
  Q_INVOKABLE void setFilters(const QMap<QString, QVariant>& filters);
  Q_INVOKABLE QMap<QString, QVariant> filters() const;
  ///@}

  ///@{
  /// maximum number of responses allowed in one query
  /// when query is at Patient level. Default is 25.
  void setMaximumPatientsQuery(const int& maximumPatientsQuery);
  int maximumPatientsQuery() const;
  ///@}

  ///@{
  /// Server
  Q_INVOKABLE ctkDICOMServer* server() const;
  Q_INVOKABLE void setServer(const ctkDICOMServer& server);
  ///@}

  /// Logger report string formatting for specific task
  Q_INVOKABLE QString loggerReport(const QString& status) override;

  /// \see ctkAbstractJob::clone()
  Q_INVOKABLE ctkAbstractJob* clone() const override;

  /// Generate worker for job
  Q_INVOKABLE ctkAbstractWorker* createWorker() override;

  /// Return the QVariant value of this job.
  ///
  /// The value is set using the ctkDICOMJobDetail metatype and is used to pass
  /// information between threads using Qt signals.
  /// \sa ctkDICOMJobDetail
  Q_INVOKABLE virtual QVariant toVariant() override;

  /// Return job type.
  Q_INVOKABLE virtual ctkDICOMJobResponseSet::JobType getJobType() const override;

protected:
  QScopedPointer<ctkDICOMQueryJobPrivate> d_ptr;

  /// Constructor allowing derived class to specify a specialized pimpl.
  ///
  /// \note You are responsible to call init() in the constructor of
  /// derived class. Doing so ensures the derived class is fully
  /// instantiated in case virtual method are called within init() itself.
  ctkDICOMQueryJob(ctkDICOMQueryJobPrivate* pimpl);

private:
  Q_DECLARE_PRIVATE(ctkDICOMQueryJob);
  Q_DISABLE_COPY(ctkDICOMQueryJob);
};

#endif
