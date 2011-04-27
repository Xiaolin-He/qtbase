/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the qmake application of the Qt Toolkit.
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

#include "symmake_abld.h"
#include "initprojectdeploy_symbian.h"

#include <qstring.h>
#include <qstringlist.h>
#include <qdir.h>
#include <qdatetime.h>
#include <qdebug.h>

// Included from tools/shared
#include <symbian/epocroot_p.h>

#define DO_NOTHING_TARGET "do_nothing"
#define CREATE_TEMPS_TARGET "create_temps"
#define EXTENSION_CLEAN "extension_clean"
#define PRE_TARGETDEPS_TARGET "pre_targetdeps"
#define COMPILER_CLEAN_TARGET "compiler_clean"
#define FINALIZE_TARGET "finalize"
#define GENERATED_SOURCES_TARGET "generated_sources"
#define ALL_SOURCE_DEPS_TARGET "all_source_deps"
#define DEPLOYMENT_TARGET "deployment"
#define DEPLOYMENT_CLEAN_TARGET "deployment_clean"
#define WINSCW_DEPLOYMENT_TARGET "winscw_deployment"
#define WINSCW_DEPLOYMENT_CLEAN_TARGET "winscw_deployment_clean"
#define STORE_BUILD_TARGET "store_build"

SymbianAbldMakefileGenerator::SymbianAbldMakefileGenerator() : SymbianMakefileGenerator() { }
SymbianAbldMakefileGenerator::~SymbianAbldMakefileGenerator() { }

void SymbianAbldMakefileGenerator::writeMkFile(const QString& wrapperFileName, bool deploymentOnly)
{
    QFile ft(gnuMakefileName);
    if (ft.open(QIODevice::WriteOnly)) {
        generatedFiles << ft.fileName();
        QTextStream t(&ft);

        t << "# ==============================================================================" << endl;
        t << "# Generated by qmake (" << qmake_version() << ") (Qt " << QT_VERSION_STR << ") on: ";
        t << QDateTime::currentDateTime().toString() << endl;
        t << "# This file is generated by qmake and should not be modified by the" << endl;
        t << "# user." << endl;
        t << "#  Name        : " << gnuMakefileName << endl;
        t << "#  Part of     : " << project->values("TARGET").join(" ") << endl;
        t << "#  Description : This file is used to call necessary targets on wrapper makefile" << endl;
        t << "#                during normal Symbian build process." << endl;
        t << "#  Version     : " << endl;
        t << "#" << endl;
        t << "# ==============================================================================" << "\n" << endl;

        t << endl << endl;

        t << "MAKE = make" << endl;
        t << endl;

        t << "VISUAL_CFG = RELEASE" << endl;
        t << "ifeq \"$(CFG)\" \"UDEB\"" << endl;
        t << "VISUAL_CFG = DEBUG" << endl;
        t << "endif" << endl;
        t << endl;

        t << DO_NOTHING_TARGET " :" << endl;
        t << "\t" << "@rem " DO_NOTHING_TARGET << endl << endl;

        QString buildDeps;
        QString cleanDeps;
        QString finalDeps;
        QString cleanDepsWinscw;
        QString finalDepsWinscw;
        QStringList wrapperTargets;
        if (deploymentOnly) {
            buildDeps.append(STORE_BUILD_TARGET);
            cleanDeps.append(DEPLOYMENT_CLEAN_TARGET);
            cleanDepsWinscw.append(WINSCW_DEPLOYMENT_CLEAN_TARGET " " DEPLOYMENT_CLEAN_TARGET);
            finalDeps.append(DEPLOYMENT_TARGET);
            finalDepsWinscw.append(WINSCW_DEPLOYMENT_TARGET " " DEPLOYMENT_TARGET);
            wrapperTargets << WINSCW_DEPLOYMENT_TARGET
                << WINSCW_DEPLOYMENT_CLEAN_TARGET
                << DEPLOYMENT_TARGET
                << DEPLOYMENT_CLEAN_TARGET
                << STORE_BUILD_TARGET;
        } else {
            buildDeps.append(CREATE_TEMPS_TARGET " " PRE_TARGETDEPS_TARGET " " STORE_BUILD_TARGET);
            cleanDeps.append(EXTENSION_CLEAN " " DEPLOYMENT_CLEAN_TARGET);
            cleanDepsWinscw.append(EXTENSION_CLEAN " " WINSCW_DEPLOYMENT_CLEAN_TARGET " " DEPLOYMENT_CLEAN_TARGET);
            finalDeps.append(FINALIZE_TARGET " " DEPLOYMENT_TARGET);
            finalDepsWinscw.append(FINALIZE_TARGET " " WINSCW_DEPLOYMENT_TARGET " " DEPLOYMENT_TARGET);
            wrapperTargets << PRE_TARGETDEPS_TARGET
                << CREATE_TEMPS_TARGET
                << EXTENSION_CLEAN
                << FINALIZE_TARGET
                << WINSCW_DEPLOYMENT_CLEAN_TARGET
                << WINSCW_DEPLOYMENT_TARGET
                << DEPLOYMENT_CLEAN_TARGET
                << DEPLOYMENT_TARGET
                << STORE_BUILD_TARGET;
        }

        t << "MAKMAKE: " << buildDeps << endl << endl;
        t << "LIB: " << buildDeps << endl << endl;
        t << "BLD: " << buildDeps << endl << endl;
        t << "ifeq \"$(PLATFORM)\" \"WINSCW\"" << endl;
        t << "CLEAN: " << cleanDepsWinscw << endl;
        t << "else" << endl;
        t << "CLEAN: " << cleanDeps << endl;
        t << "endif" << endl << endl;
        t << "CLEANLIB: " DO_NOTHING_TARGET << endl << endl;
        t << "RESOURCE: " DO_NOTHING_TARGET << endl << endl;
        t << "FREEZE: " DO_NOTHING_TARGET << endl << endl;
        t << "SAVESPACE: " DO_NOTHING_TARGET << endl << endl;
        t << "RELEASABLES: " DO_NOTHING_TARGET << endl << endl;
        t << "ifeq \"$(PLATFORM)\" \"WINSCW\"" << endl;
        t << "FINAL: " << finalDepsWinscw << endl;
        t << "else" << endl;
        t << "FINAL: " << finalDeps << endl;
        t << "endif" << endl << endl;

        QString makefile(Option::fixPathToTargetOS(fileInfo(wrapperFileName).canonicalFilePath()));
        foreach(QString target, wrapperTargets) {
            t << target << " : " << makefile << endl;
            t << "\t-$(MAKE) -f \"" << makefile << "\" " << target << " QT_SIS_TARGET=$(VISUAL_CFG)-$(PLATFORM)" << endl << endl;
        }

        t << endl;
    } // if(ft.open(QIODevice::WriteOnly))
}

void SymbianAbldMakefileGenerator::writeWrapperMakefile(QFile& wrapperFile, bool isPrimaryMakefile)
{
    QStringList allPlatforms;
    foreach(QString platform, project->values("SYMBIAN_PLATFORMS")) {
        allPlatforms << platform.toLower();
    }

    QStringList debugPlatforms = allPlatforms;
    QStringList releasePlatforms = allPlatforms;
    releasePlatforms.removeAll("winscw"); // No release for emulator

    QString testClause;
    if (project->isActiveConfig(SYMBIAN_TEST_CONFIG))
        testClause = QLatin1String(" test");
    else
        testClause = QLatin1String("");

    QTextStream t(&wrapperFile);

    MakefileGenerator::writeHeader(t);

    t << "MAKEFILE          = " << fileInfo(wrapperFile.fileName()).fileName() << endl;
    t << "QMAKE             = " << var("QMAKE_QMAKE") << endl;
    t << "DEL_FILE          = " << var("QMAKE_DEL_FILE") << endl;
    t << "DEL_DIR           = " << var("QMAKE_DEL_DIR") << endl;
    t << "DEL_TREE          = " << var("QMAKE_DEL_TREE") << endl;
    t << "MOVE              = " << var("QMAKE_MOVE") << endl;
    t << "CHK_DIR_EXISTS    = " << var("QMAKE_CHK_DIR_EXISTS") << endl;
    t << "MKDIR             = " << var("QMAKE_MKDIR") << endl;
#ifdef Q_OS_WIN32
    t << "XCOPY             = xcopy /d /f /h /r /y /i" << endl;
    t << "ABLD              = ABLD.BAT" << endl;
#elif defined(Q_OS_MAC)
    t << "XCOPY             = cp -R -v" << endl;
    t << "ABLD              = abld" << endl;
#else
    t << "XCOPY             = cp -R -u -v" << endl;
    t << "ABLD              = abld" << endl;
#endif
    t << "DEBUG_PLATFORMS   = " << debugPlatforms.join(" ") << endl;
    t << "RELEASE_PLATFORMS = " << releasePlatforms.join(" ") << endl;
    t << "MAKE              = make" << endl;
    t << endl;
    t << "ifeq (WINS,$(findstring WINS, $(PLATFORM)))" << endl;
    t << "ZDIR=$(EPOCROOT)" << QDir::toNativeSeparators("epoc32/release/$(PLATFORM)/$(CFG)/z") << endl;
    t << "else" << endl;
    t << "ZDIR=$(EPOCROOT)" << QDir::toNativeSeparators("epoc32/data/z") << endl;
    t << "endif" << endl;
    t << endl;
    t << "DEFINES" << '\t' << " = "
      << varGlue("PRL_EXPORT_DEFINES","-D"," -D"," ")
      << varGlue("QMAKE_COMPILER_DEFINES", "-D", "-D", " ")
      << varGlue("DEFINES","-D"," -D","") << endl;

    t << "INCPATH" << '\t' << " = ";

    for (QMap<QString, QStringList>::iterator it = systeminclude.begin(); it != systeminclude.end(); ++it) {
        QStringList values = it.value();
        for (int i = 0; i < values.size(); ++i) {
            t << " -I\"" << values.at(i) << "\"";
        }
    }
    t << endl;
    t << "first: default" << endl;
    if (debugPlatforms.contains("winscw"))
        t << "default: debug-winscw";
    else if (debugPlatforms.contains("armv5"))
        t << "default: debug-armv5";
    else if (debugPlatforms.size())
        t << "default: debug-" << debugPlatforms.first();
    else
        t << "default: all";

    t << endl;
    if (!isPrimaryMakefile) {
        t << "all:" << endl;
    } else {
        t << "all: debug release" << endl;
        t << endl;

        QString qmakeCmd = "\t$(QMAKE) \"" + project->projectFile() + "\" " + buildArgs();

        t << "qmake:" << endl;
        t << qmakeCmd << endl;
        t << endl;

        t << BLD_INF_FILENAME ": " << project->projectFile() << endl;
        t << qmakeCmd << endl;
        t << endl;

        t << "$(ABLD): " BLD_INF_FILENAME << endl;
        t << "\tbldmake bldfiles" << endl;
        t << endl;

        QString locFileDep = generateLocFileTarget(t, qmakeCmd);

        t << "debug: " << locFileDep << "$(ABLD)" << endl;
        foreach(QString item, debugPlatforms) {
            t << "\t$(ABLD)" << testClause << " build " << item << " udeb" << endl;
        }
        t << endl;
        t << "release: " << locFileDep << "$(ABLD)" << endl;
        foreach(QString item, releasePlatforms) {
            t << "\t$(ABLD)" << testClause << " build " << item << " urel" << endl;
        }
        t << endl;

        // For more specific builds, targets are in this form: build-platform, e.g. release-armv5
        foreach(QString item, debugPlatforms) {
            t << "debug-" << item << ": " << locFileDep << "$(ABLD)" << endl;
            t << "\t$(ABLD)" << testClause << " build " << item << " udeb" << endl;
        }

        foreach(QString item, releasePlatforms) {
            t << "release-" << item << ": " << locFileDep << "$(ABLD)" << endl;
            t << "\t$(ABLD)" << testClause << " build " << item << " urel" << endl;
        }

        t << endl;
        t << "export: $(ABLD)" << endl;
        t << "\t$(ABLD)" << testClause << " export" << endl;
        t << endl;

        t << "cleanexport: $(ABLD)" << endl;
        t << "\t$(ABLD)" << testClause << " cleanexport" << endl;
        t << endl;

    }

    // pre_targetdeps target depends on:
    //  - all targets specified in PRE_TARGETDEPS
    //  - the GENERATED_SOURCES sources (so that they get generated)
    //  - all dependencies of sources targeted for compilation
    //    (mainly to ensure that any included UNUSED_SOURCES that need to be generated get generated)
    //
    // Unfortunately, Symbian build chain doesn't support linking generated objects to target,
    // so supporting generating sources is the best we can do. This is enough for mocs.

    if (targetType != TypeSubdirs) {
        writeExtraTargets(t);
        writeExtraCompilerTargets(t);

        t << CREATE_TEMPS_TARGET ":" << endl;
        // generate command lines like this ...
        // -@ if NOT EXIST  ".\somedir"         mkdir ".\somedir"
        QStringList dirsToClean;
        QString dirExists = var("QMAKE_CHK_DIR_EXISTS");
        QString mkdir = var("QMAKE_MKDIR");
        for (QMap<QString, QStringList>::iterator it = systeminclude.begin(); it != systeminclude.end(); ++it) {
            QStringList values = it.value();
            for (int i = 0; i < values.size(); ++i) {
                if (values.at(i).endsWith("/" QT_EXTRA_INCLUDE_DIR)) {
                    QString fixedValue(QDir::toNativeSeparators(values.at(i)));
                    dirsToClean << fixedValue;
                    t << "\t-@ " << dirExists << " \""  << fixedValue << "\" "
                      << (isWindowsShell() ? "" : "|| ")
                      << mkdir << " \"" << fixedValue << "\"" << endl;
                }
            }
        }
        t << endl;

        // Note: EXTENSION_CLEAN will get called many times when doing reallyclean
        //       This is why the "2> NUL" gets appended to generated clean targets in makefile.cpp.
        t << EXTENSION_CLEAN ": " COMPILER_CLEAN_TARGET << endl;
        generateCleanCommands(t, dirsToClean, "$(DEL_TREE)", "", "", "");
        generateCleanCommands(t, project->values("QMAKE_CLEAN"), "$(DEL_FILE)", "", "", "");
        t << endl;

        t << PRE_TARGETDEPS_TARGET ":"
          << MAKEFILE_DEPENDENCY_SEPARATOR GENERATED_SOURCES_TARGET
          << MAKEFILE_DEPENDENCY_SEPARATOR ALL_SOURCE_DEPS_TARGET;
        if (project->values("PRE_TARGETDEPS").size())
            t << MAKEFILE_DEPENDENCY_SEPARATOR << project->values("PRE_TARGETDEPS").join(MAKEFILE_DEPENDENCY_SEPARATOR);
        t << endl << endl;
        t << GENERATED_SOURCES_TARGET ":";
        if (project->values("GENERATED_SOURCES").size())
            t << MAKEFILE_DEPENDENCY_SEPARATOR << project->values("GENERATED_SOURCES").join(MAKEFILE_DEPENDENCY_SEPARATOR);
        t << endl << endl;
        t << ALL_SOURCE_DEPS_TARGET ":";

        QStringList allDeps;
        for (QMap<QString, QStringList>::iterator it = sources.begin(); it != sources.end(); ++it) {
            QString currentSourcePath = it.key();
            QStringList values = it.value();
            for (int i = 0; i < values.size(); ++i) {
                // we need additional check
                QString sourceFile = currentSourcePath + "/" + values.at(i);
                QStringList deps = findDependencies(QDir::toNativeSeparators(sourceFile));
                appendIfnotExist(allDeps, deps);
            }
        }

        foreach(QString item, allDeps) {
            t << MAKEFILE_DEPENDENCY_SEPARATOR << item;
        }
        t << endl << endl;

        // Post link operations
        t << FINALIZE_TARGET ":" << endl;
        if (!project->isEmpty("QMAKE_POST_LINK")) {
            t << '\t' << var("QMAKE_POST_LINK");
            t << endl;
        }
        t << endl;
    } else {
        QList<MakefileGenerator::SubTarget*> subtargets = findSubDirsSubTargets();
        writeSubTargets(t, subtargets, SubTargetSkipDefaultVariables | SubTargetSkipDefaultTargets);
        qDeleteAll(subtargets);
    }

    // Deploymend targets for both emulator and rom deployment
    writeDeploymentTargets(t, false);
    writeDeploymentTargets(t, true);

    generateDistcleanTargets(t);

    t << "clean: $(ABLD)" << endl;
    t << "\t-$(ABLD)" << testClause << " reallyclean" << endl;
    t << "\t-bldmake clean" << endl;
    t << endl;

    t << "clean-debug: $(ABLD)" << endl;
    foreach(QString item, debugPlatforms) {
        t << "\t$(ABLD)" << testClause << " reallyclean " << item << " udeb" << endl;
    }
    t << endl;
    t << "clean-release: $(ABLD)" << endl;
    foreach(QString item, releasePlatforms) {
        t << "\t$(ABLD)" << testClause << " reallyclean " << item << " urel" << endl;
    }
    t << endl;

    // For more specific builds, targets are in this form: clean-build-platform, e.g. clean-release-armv5
    foreach(QString item, debugPlatforms) {
        t << "clean-debug-" << item << ": $(ABLD)" << endl;
        t << "\t$(ABLD)" << testClause << " reallyclean " << item << " udeb" << endl;
    }
    foreach(QString item, releasePlatforms) {
        t << "clean-release-" << item << ": $(ABLD)" << endl;
        t << "\t$(ABLD)" << testClause << " reallyclean " << item << " urel" << endl;
    }
    t << endl;

    t << "freeze: $(ABLD)" << endl;
    t << "\t$(ABLD)" << testClause << " freeze" << endl;
    t << endl;

    // Abld toolchain doesn't differentiate between freezing release or debug
    t << "freeze-debug: freeze" << endl << endl;
    t << "freeze-release: freeze" << endl << endl;

    // For more specific builds, targets are in this form: freeze-build-platform, e.g. freeze-release-armv5,
    // though note that debug and release targets of each platform are identical in symbian-abld.
    foreach(QString item, debugPlatforms) {
        t << "freeze-debug-" << item << ": $(ABLD)" << endl;
        t << "\t$(ABLD)" << testClause << " freeze " << item << endl;
    }
    foreach(QString item, releasePlatforms) {
        t << "freeze-release-" << item << ": $(ABLD)" << endl;
        t << "\t$(ABLD)" << testClause << " freeze " << item << endl;
    }

    t << endl;
}

void SymbianAbldMakefileGenerator::writeBldInfExtensionRulesPart(QTextStream& t, const QString &iconTargetFile)
{
    // We don't use extensions for anything in abld
    Q_UNUSED(t);
    Q_UNUSED(iconTargetFile);
}

bool SymbianAbldMakefileGenerator::writeDeploymentTargets(QTextStream &t, bool isRom)
{
    if (isRom)
        t << DEPLOYMENT_TARGET ":" << endl;
    else
        t << WINSCW_DEPLOYMENT_TARGET ":" << endl;

    QString remoteTestPath = qt_epocRoot()
        + QDir::toNativeSeparators(QLatin1String(isRom ? "epoc32/data/z/private/"
                                                       : "epoc32/winscw/c/private/"))
        + privateDirUid;
    DeploymentList depList;

    initProjectDeploySymbian(project, depList, remoteTestPath, false, true,
        QLatin1String(isRom ? ROM_DEPLOYMENT_PLATFORM : EMULATOR_DEPLOYMENT_PLATFORM),
        QString(), generatedDirs, generatedFiles);

    if (depList.size())
        t << "\t-echo Deploying changed files..." << endl;

    for (int i = 0; i < depList.size(); ++i) {
#ifdef Q_OS_WIN32
        // Xcopy prompts for selecting file or directory if target doesn't exist,
        // and doesn't provide switch to force file selection. It does provide dir forcing, though,
        // so strip the last part of the destination.
        t << "\t-$(XCOPY) \"" << depList.at(i).from << "\" \""
          << depList.at(i).to.left(depList.at(i).to.lastIndexOf("\\") + 1) << "\"" << endl;
#else
        QString dirExists = var("QMAKE_CHK_DIR_EXISTS");
        QString mkdir = var("QMAKE_MKDIR");
        QString dir = QFileInfo(depList.at(i).to).dir().path();
        t << "\t-@ " << dirExists << " \""  << dir << "\" || "
                      << mkdir << " \"" << dir << "\"" << endl;
        t << "\t-$(XCOPY) \"" << QDir::toNativeSeparators(depList.at(i).from) << "\" \""
          << QDir::toNativeSeparators(depList.at(i).to) << "\"" << endl;
#endif
    }

    t << endl;

    if (isRom)
        t << DEPLOYMENT_CLEAN_TARGET ":" << endl;
    else
        t << WINSCW_DEPLOYMENT_CLEAN_TARGET ":" << endl;

    QStringList cleanList;
    for (int i = 0; i < depList.size(); ++i) {
        cleanList.append(QDir::toNativeSeparators(depList.at(i).to));
    }
    generateCleanCommands(t, cleanList, "$(DEL_FILE)", "", "", "");

    // Note: If deployment creates any directories, they will not get deleted after cleanup.
    // To do this in robust fashion could be quite complex.

    t << endl;

    return true;
}

void SymbianAbldMakefileGenerator::writeBldInfMkFilePart(QTextStream& t, bool addDeploymentExtension)
{
    // Normally emulator deployment gets done via regular makefile, but since subdirs
    // do not get that, special deployment only makefile is generated for them if needed.
    if (targetType != TypeSubdirs || addDeploymentExtension) {
        gnuMakefileName = QLatin1String("Makefile_") + fileInfo(mmpFileName).completeBaseName()
            + QLatin1String(".mk");
        t << "gnumakefile " << gnuMakefileName << endl;
    }
}

void SymbianAbldMakefileGenerator::appendAbldTempDirs(QStringList& sysincspaths, QString includepath)
{
    // As a workaround for Symbian toolchain insistence to treat include
    // statements as relative to source file rather than the file they appear in,
    // we generate extra temporary include directories to make
    // relative include paths used in various headers to work properly.
    // Note that this is not a fix-all solution; it's just a stop-gap measure
    // to make Qt itself build until toolchain can support relative includes in
    // a way that Qt expects.
    QString epocPath("epoc32");
    if (!includepath.contains(epocPath)) // No temp dirs for epoc includes
        appendIfnotExist(sysincspaths, includepath + QString("/" QT_EXTRA_INCLUDE_DIR));
}
