#include "settings.h"

#include <QDebug>
#include <QSettings>
#include <QVariant>
#include <QDate>

#include <inton-core/include/config.h>

#include "applicationconfig.h"

QString SettingsKeyDate = "date_v3";
QString SettingsKeyIntensityFrame = "intensity/frame";
QString SettingsKeyIntensityShift = "intensity/shift";
QString SettingsKeyIntensitySmoothFrame = "intensity/smoothFrame";
QString SettingsKeySegmentsByIntensityMinimumLength = "segmentsByIntensity/minimumLength";
QString SettingsKeySegmentsByIntensityThresholdAbsolute = "segmentsByIntensity/thresholdAbsolute";
QString SettingsKeySegmentsByIntensityThresholdRelative = "segmentsByIntensity/thresholdRelative";
QString SettingsKeySpeechRateKCoeficient = "speechRate/K";
QString SettingsKeySpeechRateMCoeficient = "speechRate/M";

QString SettingsKeyMeanValueDegry = "speechRate/MeanValueDegry";
QString SettingsKeyKSpeechRate = "speechRate/K1";
QString SettingsKeyMinSpeechRate = "speechRate/Min";
QString SettingsKeyMaxSpeechRate = "speechRate/Max";
QString SettingsKeyKArticulationRate = "articulationRate/K2";
QString SettingsKeyMinArticulationRate = "articulationRate/Min";
QString SettingsKeyMaxArticulationRate = "articulationRate/Max";
QString SettingsKeyKMeanPauses = "meanPauses/Max";
QString SettingsKeyKFillerSounds = "fillerSounds/K4";
QString SettingsKeyMaxFillerSounds = "fillerSounds/Max";
QString SettingsKeyMinFillerSounds = "fillerSounds/Min";

Settings::Settings(QObject *parent) : QObject(parent),
  config(nullptr),
  meanValueDegry(DefaultMeanValueDegry),
  kSpeechRate(DefaultKSpeechRate),
  minSpeechRate(DefaultMinSpeechRate),
  maxSpeechRate(DefaultMaxSpeechRate),
  kArticulationRate(DefaultKArticulationRate),
  minArticulationRate(DefaultMinArticulationRate),
  maxArticulationRate(DefaultMaxArticulationRate),
  kMeanPauses(DefaultKMeanPauses),
  minFillerSounds(DefaultMinFillerSounds),
  maxFillerSounds(DefaultMaxFillerSounds),
  kFillerSounds(DefaultKFillerSounds)
{
    this->getConfig();
}

Settings::Settings(const Settings &settings) : QObject(),
    config(settings.config),
    meanValueDegry(settings.meanValueDegry),
    kSpeechRate(settings.kSpeechRate),
    minSpeechRate(settings.minSpeechRate),
    maxSpeechRate(settings.maxSpeechRate),
    kArticulationRate(settings.kArticulationRate),
    minArticulationRate(settings.minArticulationRate),
    maxArticulationRate(settings.maxArticulationRate),
    kMeanPauses(settings.kMeanPauses),
    minFillerSounds(settings.minFillerSounds),
    maxFillerSounds(settings.maxFillerSounds),
    kFillerSounds(settings.kFillerSounds)
{

}

Settings::~Settings()
{
    qDebug() << "~Settings";
}

Settings * Settings::getInstance(QObject *parent)
{
    static Settings * instance = new Settings(parent);
    return instance;
}

IntonCore::Config * Settings::getConfig()
{
    qDebug() << "getConfig";

    if (this->config == nullptr)
    {
        qDebug() << "Load new config";
        this->config = new IntonCore::Config();
        this->loadFromFile(config);
    }

    return this->config;
}

void Settings::loadFromFile(IntonCore::Config *config)
{
    QSettings settings(ApplicationConfig::GetFullSettingsPath(), QSettings::IniFormat);
    if (settings.contains(SettingsKeyDate))
    {
        qDebug() << "Load config file: " << settings.fileName();
        config->setIntensityFrame(
            settings.value(SettingsKeyIntensityFrame, DefaultFrame).toUInt()
        );
        config->setIntensityShift(
            settings.value(SettingsKeyIntensityShift, DefaultShift).toUInt()
        );
        config->setIntensitySmoothFrame(
            settings.value(SettingsKeyIntensitySmoothFrame, DefaultSmoothFrame).toUInt()
        );
        config->setSegmentsByIntensityMinimumLength(
            settings.value(SettingsKeySegmentsByIntensityMinimumLength, DefaultSegmentLimit).toUInt()
        );
        config->setSegmentsByIntensityThresholdAbsolute(
            settings.value(SettingsKeySegmentsByIntensityThresholdAbsolute).toDouble()
        );
        config->setSegmentsByIntensityThresholdRelative(
            settings.value(SettingsKeySegmentsByIntensityThresholdRelative).toDouble()
        );
        this->setMeanValueDegry(
            settings.value(SettingsKeyMeanValueDegry, DefaultMeanValueDegry),
            false
        );
        this->setKSpeechRate(
            settings.value(SettingsKeyKSpeechRate, DefaultKSpeechRate),
            false
        );
        this->setMinSpeechRate(
            settings.value(SettingsKeyMinSpeechRate, DefaultMinSpeechRate),
            false
        );
        this->setMaxSpeechRate(
            settings.value(SettingsKeyMaxSpeechRate, DefaultMaxSpeechRate),
            false
        );
        this->setKArticulationRate(
            settings.value(SettingsKeyKArticulationRate, DefaultKArticulationRate),
            false
        );
        this->setMinArticulationRate(
            settings.value(SettingsKeyMinArticulationRate, DefaultMinArticulationRate),
            false
        );
        this->setMaxArticulationRate(
            settings.value(SettingsKeyMaxArticulationRate, DefaultMaxArticulationRate),
            false
        );
        this->setKMeanPauses(
            settings.value(SettingsKeyKMeanPauses, DefaultKMeanPauses),
            false
        );
        this->setKFillerSounds(
            settings.value(SettingsKeyKFillerSounds, DefaultKFillerSounds),
            false
        );
        this->setMaxFillerSounds(
            settings.value(SettingsKeyMaxFillerSounds, DefaultMaxFillerSounds),
            false
        );
        this->setMinFillerSounds(
            settings.value(SettingsKeyMinFillerSounds, DefaultMinFillerSounds),
            false
        );
    }
}

void Settings::saveToFile(IntonCore::Config *config)
{
    QSettings settings(ApplicationConfig::GetFullSettingsPath(), QSettings::IniFormat);

    qDebug() << "Create new config file: " << settings.fileName();
    settings.setValue(
        SettingsKeyDate,
        QDate()
    );
    settings.setValue(
        SettingsKeyIntensityFrame,
        config->intensityFrame()
    );
    settings.setValue(
        SettingsKeyIntensityShift,
        config->intensityShift()
    );
    settings.setValue(
        SettingsKeyIntensitySmoothFrame,
        config->intensitySmoothFrame()
    );
    settings.setValue(
        SettingsKeySegmentsByIntensityMinimumLength,
        config->segmentsByIntensityMinimumLength()
    );
    settings.setValue(
        SettingsKeySegmentsByIntensityThresholdAbsolute,
        config->segmentsByIntensityThresholdAbsolute()
    );
    settings.setValue(
        SettingsKeySegmentsByIntensityThresholdRelative,
        config->segmentsByIntensityThresholdRelative()
    );
    settings.setValue(
        SettingsKeyMeanValueDegry,
        this->getMeanValueDegry()
    );
    settings.setValue(
        SettingsKeyKSpeechRate,
        this->getKSpeechRate()
    );
    settings.setValue(
        SettingsKeyMinSpeechRate,
        this->getMinSpeechRate()
    );
    settings.setValue(
        SettingsKeyMaxSpeechRate,
        this->getMaxSpeechRate()
    );
    settings.setValue(
        SettingsKeyKArticulationRate,
        this->getKArticulationRate()
    );
    settings.setValue(
        SettingsKeyMinArticulationRate,
        this->getMinArticulationRate()
    );
    settings.setValue(
        SettingsKeyMaxArticulationRate,
        this->getMaxArticulationRate()
    );
    settings.setValue(
        SettingsKeyKMeanPauses,
        this->getKMeanPauses()
    );
    settings.setValue(
        SettingsKeyKFillerSounds,
        this->getKFillerSounds()
    );
    settings.setValue(
        SettingsKeyMaxFillerSounds,
        this->getMaxFillerSounds()
    );
    settings.setValue(
        SettingsKeyMinFillerSounds,
        this->getMinFillerSounds()
    );
    settings.sync();
}

QVariant Settings::getIntensityFrame()
{
    IntonCore::Config * config = this->getConfig();
    return config->intensityFrame();
}

void Settings::setIntensityFrame(QVariant value, bool save)
{
    IntonCore::Config * config = this->getConfig();
    config->setIntensityFrame(value.toUInt());
    if (save) this->saveToFile(config);
}

QVariant Settings::getIntensityShift()
{
    IntonCore::Config * config = this->getConfig();
    return config->intensityShift();
}

void Settings::setIntensityShift(QVariant value, bool save)
{
    IntonCore::Config * config = this->getConfig();
    config->setIntensityShift(value.toUInt());
    if (save) this->saveToFile(config);
}

QVariant Settings::getIntensitySmoothFrame()
{
    IntonCore::Config * config = this->getConfig();
    return config->intensitySmoothFrame();
}

void Settings::setIntensitySmoothFrame(QVariant value, bool save)
{
    IntonCore::Config * config = this->getConfig();
    config->setIntensitySmoothFrame(value.toUInt());
    if (save) this->saveToFile(config);
}

QVariant Settings::getIntensityMaxLengthValue()
{
    IntonCore::Config * config = this->getConfig();
    return config->segmentsByIntensityMinimumLength();
}

void Settings::setIntensityMaxLengthValue(QVariant value, bool save)
{
    IntonCore::Config * config = this->getConfig();
    config->setSegmentsByIntensityMinimumLength(value.toUInt());
    if (save) this->saveToFile(config);
}

QVariant Settings::getSegmentsByIntensityMinimumLength()
{
    IntonCore::Config * config = this->getConfig();
    return config->segmentsByIntensityMinimumLength();
}

void Settings::setSegmentsByIntensityMinimumLength(QVariant value, bool save)
{
    IntonCore::Config * config = this->getConfig();
    config->setSegmentsByIntensityMinimumLength(value.toUInt());
    if (save) this->saveToFile(config);
}

QVariant Settings::getSegmentsByIntensityThresholdAbsolute()
{
    IntonCore::Config * config = this->getConfig();
    return config->segmentsByIntensityThresholdAbsolute();
}

void Settings::setSegmentsByIntensityThresholdAbsolute(QVariant value, bool save)
{
    IntonCore::Config * config = this->getConfig();
    config->setSegmentsByIntensityThresholdAbsolute(value.toDouble());
    if (save) this->saveToFile(config);
}

QVariant Settings::getSegmentsByIntensityThresholdRelative()
{
    IntonCore::Config * config = this->getConfig();
    return config->segmentsByIntensityThresholdRelative();
}

void Settings::setSegmentsByIntensityThresholdRelative(QVariant value, bool save)
{
    IntonCore::Config * config = this->getConfig();
    config->setSegmentsByIntensityThresholdRelative(value.toDouble());
    if (save) this->saveToFile(config);
}

void Settings::setMeanValueDegry(QVariant value, bool save)
{
    this->meanValueDegry = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getMeanValueDegry()
{
    return this->meanValueDegry;
}

void Settings::setKSpeechRate(QVariant value, bool save)
{
    this->kSpeechRate = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getKSpeechRate()
{
    return this->kSpeechRate;
}

void Settings::setMinSpeechRate(QVariant value, bool save)
{
    this->minSpeechRate = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getMinSpeechRate()
{
    return this->minSpeechRate;
}

void Settings::setMaxSpeechRate(QVariant value, bool save)
{
    this->maxSpeechRate = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getMaxSpeechRate()
{
    return this->maxSpeechRate;
}

void Settings::setKArticulationRate(QVariant value, bool save)
{
    this->kArticulationRate = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getKArticulationRate()
{
    return this->kArticulationRate;
}

void Settings::setMinArticulationRate(QVariant value, bool save)
{
    this->minArticulationRate = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getMinArticulationRate()
{
    return this->minArticulationRate;
}

void Settings::setMaxArticulationRate(QVariant value, bool save)
{
    this->maxArticulationRate = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getMaxArticulationRate()
{
    return this->maxArticulationRate;
}

void Settings::setKMeanPauses(QVariant value, bool save)
{
    this->kMeanPauses = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getKMeanPauses()
{
    return this->kMeanPauses;
}

void Settings::setKFillerSounds(QVariant value, bool save)
{
    this->kFillerSounds = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getKFillerSounds()
{
    return this->kFillerSounds;
}

void Settings::setMinFillerSounds(QVariant value, bool save)
{
    this->minFillerSounds = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getMinFillerSounds()
{
    return this->minFillerSounds;
}

void Settings::setMaxFillerSounds(QVariant value, bool save)
{
    this->maxFillerSounds = value.toDouble();
    if (save) this->saveToFile(config);
}

QVariant Settings::getMaxFillerSounds()
{
    return this->maxFillerSounds;
}

static bool advanced = false;

void Settings::setAdvanced(QVariant value)
{
    advanced = value.toBool();
}

QVariant Settings::getAdvanced()
{
    return advanced;
}
