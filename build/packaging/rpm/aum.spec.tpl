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
mkdir -p %{buildroot}/%{_libdir}
cp -r ./libaum.so %{buildroot}/%{_libdir}

%files
/usr/local/include
%{_libdir}/libaum.so

%changelog

