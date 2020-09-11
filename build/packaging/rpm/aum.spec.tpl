Name:       {NAME}
Version:    {VERSION}
Release:    1
Summary:    {DESCRIPTION}
License:    LGPLv2+
Requires:   CUnit

%description
{DESCRIPTION}

%prep


%build

%install
mkdir -p %{buildroot}/usr/local/
cp -r ./include %{buildroot}/usr/local/
cp -r ./libaum.so %{_libdir}

%files
/usr/local/include

%changelog

