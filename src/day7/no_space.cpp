#include <bits/stdc++.h>
#include <cassert>
#include <cstdint>
#include <functional>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <util.h>
#include <vector>

struct FileObject
{
    std::string name;
};

struct File : public FileObject
{
    uint32_t size;
};

struct Directory : public FileObject
{
    bool is_populated = false;
    std::vector<File> files;
    std::vector<Directory*> directories;
    Directory* parent = nullptr;
};

class FileSystem
{
private:
    Directory* root;
    Directory* current_directory;
public:

    FileSystem()
    {
        Directory* root_dir = new Directory();
        root_dir->name = "/";
        root = root_dir;
        current_directory = root_dir;
    }

    [[nodiscard]] auto cd(const std::string& directory) noexcept -> bool
    {
        if (current_directory == root) return false;
        else if (directory == "..")
        {
            current_directory = current_directory->parent;
        }
    }

    auto populate_file_objects(const std::vector<FileObject*>& objects) noexcept -> void
    {
        for (FileObject* object : objects)
        {
            File* file = dynamic_cast<File*>(object);
            Directory* directory = dynamic_cast<Directory*>(object);
            if (file)
            {
                current_directory->files.emplace_back(file);
            }
            else if (directory)
            {
                current_directory->directories.emplace_back(directory);
            }
            else
            {
                // something bad happened
                return;
            }
        }
        current_directory->is_populated = true;
    }
};

enum CommandType
{
    NONE,
    CD,
    LS
};

struct Command
{
    CommandType type;
    std::string args;
};

class LineParser
{
public:
    auto is_command(const std::string& line) const noexcept -> bool
    {
        return line[0] == '$';
    }

    auto parse_command_line(const std::string& line) const noexcept -> Command
    {
        assert(is_command(line));

        return Command {
            .type = std::invoke([&line]() {
                std::string command_text = line.substr(2, 2);
                if (command_text == "ls") return CommandType::LS;
                else return CommandType::CD;
            }),
            .args = std::invoke([&line]() {
                if (line.length() < 4) return std::string("");
                else return line.substr(4);
            })
        };
    }

    auto is_output(const std::string& line) const noexcept -> bool
    {
        return line[0] != '$';
    }

    template<typename FileObject>
    auto parse_output(const std::string& line) const noexcept -> FileObject
    {
        if (line.substr(0, 3) == "dir")
        {
        }
    }
};

auto traverse_directories(const std::vector<std::string>& commands) noexcept -> void
{

}

int main()
{
    // Get text from input file and make it didn't fail.
    const auto text = dc::get_text_in_file("inputs/7_test.txt");
    //const auto text = dc::get_text_in_file("inputs/7_input.txt");
    if (!text.has_value())
    {
        std::cerr << "Failed to get text in file." << std::endl;
        return EXIT_FAILURE;
    }

    LineParser parser;
    FileSystem file_system;

    uint32_t line_count = 0;
    for (auto line : text.value())
    {
        if (parser.is_command(const std::string &line))
        line_count++;
    }

}