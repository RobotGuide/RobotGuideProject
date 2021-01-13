#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_BUFFER_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_BUFFER_H

namespace robotguide::com::transportlayer
{
	class Buffer
	{
	private:
		char* buffer;
		const unsigned int maxLength;
		unsigned int length;
	public:
		Buffer(const unsigned int maxLength);
		~Buffer();

		Buffer(const Buffer& buffer);
		Buffer& operator=(const Buffer&) = delete;

		/// <summary>
		/// Returns if this buffer contains data
		/// </summary>
		/// <returns>True if the buffer has data</returns>
		bool HasData() const;

		/// <summary>
		/// Get the character buffer
		/// </summary>
		/// <returns>The character buffer</returns>
		char* GetBuffer() const;

		/// <summary>
		/// The maximum length this buffer can hold
		/// </summary>
		unsigned int GetMaxLength() const;

		/// <summary>
		/// The current length of this buffer
		/// </summary>
		int GetLength() const;

		/// <summary>
		/// Set the length of the current buffer
		/// </summary>
		/// <param name="bytes">The amount of bytes this buffer holds</param>
		void SetLength(const unsigned int bytes);

		/// <summary>
		/// Clear all characters in the buffer
		/// </summary>
		void Clear();
	};
}
#endif
