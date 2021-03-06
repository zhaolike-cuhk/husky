// Copyright 2016 Husky Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <fstream>
#include <string>

#include "hdfs/hdfs.h"

#include "base/serialization.hpp"
#include "io/input/binary_inputformat_impl.hpp"

namespace husky {
namespace io {

class HDFSFileBinStream : public FileBinStreamBase {
   public:
    HDFSFileBinStream(hdfsFS fs, const std::string& filename);
    size_t size() const override;
    void* pop_front_bytes(size_t sz) override;
    ~HDFSFileBinStream();

   protected:
    void read(char* buf, size_t sz) override;

   private:
    hdfsFS fs_;
    hdfsFile file_ = nullptr;
    size_t file_size_;
};

class HDFSFileAsker {
   public:
    void init(const std::string& path, const std::string& filter = "");
    std::string fetch_new_file();

   private:
    std::string file_url_;
};

class HDFSBinaryInputFormat : public BinaryInputFormatImpl {
   public:
    HDFSBinaryInputFormat();
    ~HDFSBinaryInputFormat();
    void set_input(const std::string& path, const std::string& filter = "") override;
    // Should not used by user
    bool next(BinaryInputFormatImpl::RecordT& record) override;

   protected:
    hdfsFS fs_;
    HDFSFileAsker asker_;
};

}  // namespace io
}  // namespace husky
