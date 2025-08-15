# clean.ps1

$extensions = @("*.obj", "*.exe", "*.pdb", "*.ilk", "*.log")

foreach ($ext in $extensions) {
    Get-ChildItem -Path . -Filter $ext -Recurse | Remove-Item -Force
}

Write-Host "Clean complete. Removed: $($extensions -join ', ')"
