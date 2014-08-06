#include <unordered_map>
#include <cassert>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/format.hpp>
#include "make_unique.hpp"
#include "log.hpp"

using namespace MiniPos;

struct Log::Impl
{
    struct ETypeHasher
    {
        std::size_t operator()(const EType &t) const
        {
            return std::hash<unsigned char>()(static_cast<unsigned char>(t));
        }
    };

    struct StorageStruct
    {
        bool MultiStream;
        bool Initialized;

        std::unordered_map<Log::EType, std::string, ETypeHasher> LogTypeHash;

        std::ostream *LogOutputStream;

        std::ofstream LogOutputFileStream;
        std::string LogOutputDirectoryPath;
        std::string LogOutputFilePrefix;
        std::string LogOutputFilePath;
    };

    typedef std::unique_ptr<StorageStruct> Storage_ptr;

    std::mutex StorageMutex;
    Storage_ptr StorageInstance;

    std::mutex LogMutex;

    Impl();
    ~Impl();

    StorageStruct *Storage();
};

std::unique_ptr<Log::Impl> Log::s_pimpl = std::make_unique<Log::Impl>();

void Log::Initialize(std::ostream &out_outputStream)
{
    if (s_pimpl->Storage()->Initialized)
        return;

    s_pimpl->Storage()->LogOutputStream = &out_outputStream;

    if (!s_pimpl->Storage()->MultiStream)
        s_pimpl->Storage()->Initialized = true;
}

void Log::Initialize(const std::string &outputDirectoryPath,
                     const std::string &outputFilePrefix)
{
    if (s_pimpl->Storage()->Initialized)
        return;

    s_pimpl->Storage()->LogOutputDirectoryPath = outputDirectoryPath;
    s_pimpl->Storage()->LogOutputFilePrefix = outputFilePrefix;

    if (boost::filesystem::exists(s_pimpl->Storage()->LogOutputDirectoryPath)) {
        if (!boost::filesystem::is_directory(s_pimpl->Storage()->LogOutputDirectoryPath)) {
            boost::filesystem::remove(s_pimpl->Storage()->LogOutputDirectoryPath);
        }
    }

    if (!boost::filesystem::exists(s_pimpl->Storage()->LogOutputDirectoryPath)) {
        boost::filesystem::create_directories(s_pimpl->Storage()->LogOutputDirectoryPath);
    }

    s_pimpl->Storage()->LogOutputFilePath =
            (boost::filesystem::path(s_pimpl->Storage()->LogOutputDirectoryPath)
             / boost::filesystem::path((boost::format("%1%_%2%.txt")
                                        % s_pimpl->Storage()->LogOutputFilePrefix
                                        % boost::algorithm::replace_all_copy(
                                            boost::algorithm::replace_all_copy(
                                                boost::posix_time::to_simple_string(
                                                    boost::posix_time::second_clock::local_time()),
                                                ":", "-"),
                                            " ", "_")).str())).string();

    if (!s_pimpl->Storage()->MultiStream)
        s_pimpl->Storage()->Initialized = true;
}

void Log::Initialize(std::ostream &out_outputStream,
                     const std::string &outputDirectoryPath,
                     const std::string &outputFilePrefix)
{
    if (s_pimpl->Storage()->Initialized)
        return;

    s_pimpl->Storage()->MultiStream = true;

    Initialize(out_outputStream);
    Initialize(outputDirectoryPath, outputFilePrefix);

    s_pimpl->Storage()->Initialized = true;
}

Log::Log(EType type, const std::string &file, const std::string &func, int line, ...)
    : m_hasEntries(false)
{
    assert(s_pimpl->Storage()->Initialized);

    m_buffer << "[ " << boost::posix_time::second_clock::local_time()
             << " " << s_pimpl->Storage()->LogTypeHash[type]
                << " " << line << " " << func << " " << file << " ]"
                << "\n";
}

Log::~Log()
{
    m_buffer << "\n\n";
    m_buffer.flush();

    std::lock_guard<std::mutex> lock(s_pimpl->LogMutex);
    (void)lock;

    if (s_pimpl->Storage()->LogOutputStream) {
        (*s_pimpl->Storage()->LogOutputStream) << m_buffer.str();
        s_pimpl->Storage()->LogOutputStream->flush();
    }

    if (s_pimpl->Storage()->LogOutputFilePath != "") {
        if(!s_pimpl->Storage()->LogOutputFileStream.is_open()) {
            s_pimpl->Storage()->LogOutputFileStream.open(
                        s_pimpl->Storage()->LogOutputFilePath,
                        std::ios_base::out | std::ios_base::app);
            s_pimpl->Storage()->LogOutputFileStream.imbue(
                        std::locale(
                            s_pimpl->Storage()->LogOutputFileStream.getloc(),
                            new boost::posix_time::time_facet()));
        }

        s_pimpl->Storage()->LogOutputFileStream << m_buffer.str();
        s_pimpl->Storage()->LogOutputFileStream.flush();
        s_pimpl->Storage()->LogOutputFileStream.close();
    }
}

Log::Impl::Impl()
{

}

Log::Impl::~Impl()
{
    std::lock_guard<std::mutex> lock(StorageMutex);
    (void)lock;

    StorageInstance.reset();
}

Log::Impl::StorageStruct *Log::Impl::Storage()
{
    std::lock_guard<std::mutex> lock(StorageMutex);
    (void)lock;

    if (StorageInstance == nullptr) {
        StorageInstance = std::make_unique<StorageStruct>();

        StorageInstance->MultiStream = false;
        StorageInstance->Initialized = false;

        StorageInstance->LogTypeHash.clear();
        StorageInstance->LogTypeHash[Log::EType::Trace] = "TRACE";
        StorageInstance->LogTypeHash[Log::EType::Debug] = "DEBUG";
        StorageInstance->LogTypeHash[Log::EType::Info] = "INFO";
        StorageInstance->LogTypeHash[Log::EType::Warning] = "WARNING";
        StorageInstance->LogTypeHash[Log::EType::Error] = "ERROR";
        StorageInstance->LogTypeHash[Log::EType::Fatal] = "FATAL";

        StorageInstance->LogOutputStream = NULL;

        if (StorageInstance->LogOutputFileStream.is_open())
            StorageInstance->LogOutputFileStream.close();

        StorageInstance->LogOutputDirectoryPath.clear();;
        StorageInstance->LogOutputFilePrefix.clear();;
        StorageInstance->LogOutputFilePath.clear();;
    }

    return StorageInstance.get();
}

