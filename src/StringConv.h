namespace BulletSharp
{
	private ref class StringConv
	{
	public:
		static String^ UnmanagedToManaged( const char* string );
		static const char* ManagedToUnmanaged( String^ string );
	};
};
