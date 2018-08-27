#pragma once

#include "ivi-logging-console.h"

namespace logging {

class FileLogData : public StreamLogData {
public:
	~FileLogData() {
		flushLog();
	}

};

class FileLogContext : public StreamLogContextAbstract {
public:
	typedef FileLogData LogDataType;

    FILE* getFile(logging::StreamLogData&) override {
        return getFileStatic();
    }

    static void openFile(const char* fileName) {
        setFilePath(fileName);
    }

    static void setFilePath(const char* fileName) {
        if (getFileStatic() != nullptr) {
            fclose(getFileStatic());
        }
        getFileStatic() = fopen(fileName, "w");
        assert(getFileStatic() != nullptr);
    }

    FileLogContext(){toFile=true;}

private:
    struct FileWrapper{
        FILE* m_file=nullptr;
        ~FileWrapper(){
            if (m_file != nullptr) {
                fclose(m_file);
            }
        }
        FileWrapper() = default;
        FileWrapper(const FileWrapper&) = delete;
        FileWrapper(FileWrapper&&) = delete;
        FileWrapper& operator=(const FileWrapper&) = delete;
        FileWrapper& operator=(FileWrapper&&) = delete;
    };
    static FILE*& getFileStatic() {
        static FileWrapper wrapper;
        return wrapper.m_file;
    }

};

}
