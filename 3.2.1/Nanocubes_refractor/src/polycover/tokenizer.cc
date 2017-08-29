#include "tokenizer.hh"

#include <stdexcept>

namespace polycover {

namespace tokenizer {

//-----------------------------------------------------------------------------
// Tokenizer::iterator Impl.
//-----------------------------------------------------------------------------

Tokenizer::iterator::iterator(Tokenizer& tokenizer, pointer ptr) :
    tokenizer(tokenizer), ptr(ptr) {
    // std::cout << "iterator: " << (void*) ptr << std::endl;
}

//// pos-increment
//auto Tokenizer::iterator::operator++(int) -> iterator& {
//    if (ptr)
//        ptr = tokenizer.next();
//    ptr+=STORAGE_SIZE*delta; return *this;
//}

// pre-increment
auto Tokenizer::iterator::operator++() -> iterator& {
    if (ptr)
        ptr = tokenizer.next();
    return *this;
}

// dereference and access members (doesn't make sense for char)
auto Tokenizer::iterator::operator*() const -> reference {
    if (ptr)
        return *ptr;
    else
        throw std::runtime_error("ooooops");
}

auto Tokenizer::iterator::operator->() const -> pointer {
    return ptr;
}

bool Tokenizer::iterator::operator==(const iterator& rhs) const {
    return ptr == rhs.ptr;
}

bool Tokenizer::iterator::operator!=(const iterator& rhs) const {
    return ptr != rhs.ptr;
}

//-----------------------------------------------------------------------------
// Tokenizer Impl.
//-----------------------------------------------------------------------------

Tokenizer::Tokenizer(std::istream &is, char delim, bool consider_empty):
    is_ptr(&is),
    delim(delim),
    consider_empty(consider_empty)
{}

Tokenizer::Tokenizer(char delim, bool consider_empty):
    delim(delim),
    consider_empty(consider_empty)
{}
//Tokenizer::Tokenizer(std::string st, char delim, bool consider_empty):
//    is_ptr(&ss),
//    ss(st),
//    delim(delim),
//    consider_empty(consider_empty)
//{}
//
//Tokenizer::Tokenizer(std::vector<char> &&vec, char delim, bool consider_empty):
//    is_ptr(&ss),
//    delim(delim),
//    consider_empty(consider_empty)
//{
//    characters = std::move(vec);
//    ss.rdbuf()->pubsetbuf(reinterpret_cast<char*>(&characters[0]), characters.size());
//}
    
std::string *Tokenizer::next()
{
    std::istream& is = *is_ptr;

    std::stringstream output_stream;

    while (true) {
        output_stream.str("");
        // bool eof = false;
        bool has_data = false;
        while (true) {
            is.getline(buffer, BUFFER_SIZE-1, delim);
            if (is.gcount()) {
                has_data = true;
                output_stream << buffer;
            }
            if (is.eof()) {
                // eof=true;
                break;
            }
            else if (!is.fail()) {
                break;
            }
            else {
                is.clear();
            }
        }

        if (!has_data) {
            return nullptr;
        }

        token = output_stream.str();

        if (!this->consider_empty && token.size() == 0) {
            continue;
        }
        return &token;
    }
}

Tokenizer::iterator Tokenizer::begin()
{
    return iterator(*this, next());
}

Tokenizer::iterator Tokenizer::end()
{
    return iterator(*this, nullptr);
}

std::vector<std::string> Tokenizer::readAll()
{
    std::vector<std::string> result;
    while (std::string *st = next()) {
        result.push_back(*st);
    }
    return result;
}
    
    
void Tokenizer::setInputStream(std::istream &is) {
    this->is_ptr = &is;
}


//-----------------------------------------------------------------------------
// StringTokenizer Impl.
//-----------------------------------------------------------------------------
    
StringTokenizer::StringTokenizer(const std::string& st, char delim, bool consider_empty):
    Tokenizer(delim, consider_empty),
    ss(st)
{
    this->setInputStream(ss);
}
    
//-----------------------------------------------------------------------------
// VectorTokenizer Impl.
//-----------------------------------------------------------------------------
    
VectorTokenizer::VectorTokenizer(std::vector<char>& vec, char delim, bool consider_empty):
    Tokenizer(delim, consider_empty),
    is_vec(vec),
    is(&is_vec)
{
    this->setInputStream(is);
}

} // tokenizer

} // polycover
