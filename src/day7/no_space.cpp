#include <bits/stdc++.h>
#include <util.h>

struct File
{
    std::string name;
    uint32_t size;
};

struct Directory
{
    std::string name;
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

    template<typename FileObject>
    auto populate_file_objects(const std::vector<FileObject*>& objects) noexcept -> void
    {
        for (FileObject* object : objects)
        {
            if constexpr(std::is_same<FileObject, File>::value)
            {
                current_directory->files.emplace_back(*object);
            }
            if constexpr(std::is_same<FileObject, Directory>::value)
            {
                current_directory->directories.emplace_back(object);
            }
        }
        current_directory->is_populated = true;
    }

    /** Recursively iterate through directories (DFS) */
    auto for_each_file_recursively(const Directory* root, std::function<void(const File&)> file_callback) const noexcept -> void
    {
        if (root->is_populated)
        {
            return;
        }
        if (!root->files.empty())
        {
            for (File file : root->files)
            {
                file_callback(file);
            }
        }
        if (!root->directories.empty())
        {
            for (Directory* dir : root->directories)
            {
                for_each_file_recursively(dir, file_callback);
            }
        }
    }

    auto for_each_file(const Directory* root, std::function<void(const File&)> file_callback) const noexcept -> void
    {
        if (root->is_populated)
        {
            return;
        }
        if (!root->files.empty())
        {
            for (File file : root->files)
            {
                file_callback(file);
            }
        }
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
        Command command;
        if (parser.is_command(line))
        {
            command = parser.parse_command_line(line);
        }
        else
        {

        }
        line_count++;
    }

    uint32_t total_size = 0;
    

    std::cout << total_size << std::endl;

}