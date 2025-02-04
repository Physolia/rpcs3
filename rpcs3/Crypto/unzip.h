#pragma once

std::vector<u8> unzip(const void* src, usz size);

template<typename T>
std::vector<u8> unzip(const T& src)
{
	return unzip(src.data(), src.size());
}

bool unzip(const void* src, usz size, fs::file& out);

template<typename T>
bool unzip(const std::vector<u8>& src, fs::file& out)
{
	return unzip(src.data(), src.size(), out);
}

std::vector<u8> zip(const void* src, usz size);

template<typename T>
std::vector<u8> zip(const T& src)
{
	return zip(src.data(), src.size());
}

bool zip(const void* src, usz size, fs::file& out);

template<typename T>
bool zip(const T& src, fs::file& out)
{
	return zip(src.data(), src.size(), out);
}
