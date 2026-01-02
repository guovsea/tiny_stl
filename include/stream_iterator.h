#ifndef TINYSTL_STREAM_ITERATOR_H
#define TINYSTL_STREAM_ITERATOR_H

#include <assert.h>
#include <string>

#include "iterator.h"
namespace tinystl {
	template<typename T, typename CharT = char,
		typename Traits = std::char_traits<CharT>, typename Dist = ptrdiff_t>
	class istream_iterator : public iterator<input_iterator_tag, T, Dist> {
		friend bool operator==(const istream_iterator &lhs, const istream_iterator &rhs) {
			return lhs.stream_ == rhs.stream_;
		}

		friend bool operator!=(const istream_iterator &lhs, const istream_iterator &rhs) {
			return !(lhs == rhs);
		}

	public:
		using char_type = CharT;
		using traits_type = Traits;
		using istream_type = std::basic_istream<CharT, Traits>;

		istream_iterator() : stream_{nullptr}, value_{} {}
		istream_iterator(istream_type& is) : stream_{std::addressof(is)}, value_{} {
			read();
		}
		istream_iterator(const istream_iterator&) = default;
		istream_iterator& operator=(const istream_iterator&) = default;
		~istream_iterator() = default;

		const T& operator*() const noexcept {
			assert(stream_);
			return value_;
		}
		const T* operator->() const noexcept {
			return std::addressof(*this);
		}
		istream_iterator operator++() noexcept{
			read();
			return *this;
		}
		istream_iterator operator++(int) {
			istream_iterator tmp = *this;
			++*this;
			return tmp;
		}

	private:
		void read() {
			// stream_ 不空就读，读到 eof 就将 steam_ 置空
			if (stream_ && !(*stream_ >> value_)) {
				stream_ = nullptr;
			}
		}
		istream_type* stream_;
		T value_;
	};

	// todo ostream_iterator
}

#endif // TINYSTL_STREAM_ITERATOR_H